/*
 * This file is part of Autocalibration Codebase.
 *
 * The Autocalibration Codebase is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Autocalibration Codebase is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Autocalibration Codebase.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2015 Autocalibration <nubots@nubots.net>
 */

#include "View.h"

#include <iostream>

#include <vector>

#include <chrono>
#include <iostream>


#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"


#include "utility/autocal/GraphicsTools.h"
#include "message/support/Configuration.h"

namespace module {
namespace psmove {

    using message::support::Configuration;

    //Define the key input callback  
	void View::handleInput(const sf::Window& w, double time_since_start){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
		    std::cout << "Exiting .." << std::endl;
		    running = false;
		}
	}

    View::View(std::unique_ptr<NUClear::Environment> environment)
    : Reactor(std::move(environment)) {

        on<Configuration>("View.yaml").then("Config",[this] (const Configuration& config) {
            // Use configuration here from file View.yaml
        	width = config["width"].as<int>();
		    height = config["height"].as<int>();
	    	fps = config["fps"].as<float>();
	    	frame_duration = 1.0 / fps;
        });

        on<Startup>().then("Startup",[this]{
			window = std::make_unique<sf::Window>(sf::VideoMode(640*2, 480*2), "OpenGL");
	        window->setActive(true);

		    //GLEW
		    bool success = setUpOpenGL();
	  	    if(!success){
	  	    	std::cout << "OpenGL Setup Failed! Shutting down" << std::endl; 
			    powerplant.shutdown();
			}
			//Psmove
		    psmoveTracker.init();
		    
		    //Check errors
		    checkGLError();
  
        });

		   //Main Loop  
        on<Every<60,Per<std::chrono::seconds>>, Single>().then("Tracking/Render Loop",[this]{
	        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();    
	        double frame_time_since_start = std::chrono::duration_cast<std::chrono::milliseconds>(now-start_time).count() / float(std::milli::den);  
	        // std::cout << "Frame time = " << frame_time_since_start << std::endl;
    		
    		if(video_frames * frame_duration < frame_time_since_start){
	            video_frames++;
	        } else {
	            return;
	        }

	        window->setActive(true);

	        // // Clear color buffer  
	        glClear(GL_COLOR_BUFFER_BIT);
	        
	        psmoveTracker.update();
	        psmoveTracker.render();

	        //Draw red crosshair for aiming camera
	        drawCrossHair();

	        //Get interaction
	        handleInput(*window, frame_time_since_start);
	        
	        //Display what we have drawn
	        window->display();

	        //Shutdown if necessary
	        if(!running){
	            powerplant.shutdown();
	        }
        });

		on<Shutdown>().then([this]{
			//Compute final average framerate
			std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();    
		    double finish_time = std::chrono::duration_cast<std::chrono::milliseconds>(now-start_time).count() / float(std::milli::den);     
		    std::cout << "average video framerate = " << double(video_frames) / finish_time << " Hz " << std::endl; 

		});

    }
}
}
