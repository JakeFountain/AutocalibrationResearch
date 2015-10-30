/*
 * This file is part of NUbots Codebase.
 *
 * The NUbots Codebase is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The NUbots Codebase is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the NUbots Codebase.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2015 NUbots <nubots@nubots.net>
 */

#include "Record.h"

#include <iostream>

#include <vector>

#include <chrono>
#include <iostream>


#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"


#include "utility/autocal/GraphicsTools.h"
#include "messages/support/Configuration.h"

namespace modules {
namespace psmove {

    using messages::support::Configuration;

    //Define the key input callback  
	void Record::handleInput(GLFWwindow* window, double time_since_start){

        if(glfwGetKey(window,GLFW_KEY_ESCAPE)){
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

    }

    Record::Record(std::unique_ptr<NUClear::Environment> environment)
    : Reactor(std::move(environment)) {

        on<Configuration>("Record.yaml").then([this] (const Configuration& config) {
            // Use configuration here from file Record.yaml
        	width = config["width"].as<int>();
		    height = config["height"].as<int>();
        });

        on<Startup>().then([this]{

		    //Setup a window object  
		    window = setUpGLWindow(width, height);
		    //Sets the key callback  

		    
		    psmoveTracker.init();
		    
		    std::stringstream filename;
		    start_time = NUClear::clock::now();
		    filename << std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(start_time.time_since_epoch()).count()) << ".avi";
		    video_frames = 0; 


		    //TODO: use opencv c++ bindings
		    writer = cvCreateVideoWriter(filename.str().c_str(),
		        CV_FOURCC('M','J','P','G'), 30, cvSize(width, height), 1);

		    checkGLError();
 
		    glfwPollEvents();
 
        });

		   //Main Loop  
        on<Every<60,Per<std::chrono::seconds>>, Single>().then([this]{
        	video_frames++;
	        auto now = NUClear::clock::now();    
	        double frame_time_since_start = std::chrono::duration_cast<std::chrono::milliseconds>(now-start_time).count() / float(std::milli::den);  
	        std::cout << "Frame time = " << frame_time_since_start << std::endl;
    		
    		glfwMakeContextCurrent(window);  

	        // // Clear color buffer  
	        glClear(GL_COLOR_BUFFER_BIT);
	        
	        psmoveTracker.update();
	        psmoveTracker.render();
	        psmoveTracker.saveFrame(writer);
	        psmoveTracker.savePoses();

	        drawCrossHair();

	        //Swap buffers  
	        glfwSwapBuffers(window);  
	        //Get and organize events, like keyboard and mouse input, window resizing, etc...  
	        //glfwPollEvents();  

	        handleInput(window, frame_time_since_start);

	        if(glfwWindowShouldClose(window)) {
	            powerplant.shutdown();
	        }
        });

		on<Shutdown>().then([this]{
			auto now = NUClear::clock::now();    
		    double finish_time = std::chrono::duration_cast<std::chrono::milliseconds>(now-start_time).count() / float(std::milli::den);     
		    // std::cout << "average draw framerate = " << double(frames) / finish_time << " Hz " << std::endl; 
		    std::cout << "average video framerate = " << double(video_frames) / finish_time << " Hz " << std::endl; 
		    destroyGLWindow(window);
		});

    }
}
}