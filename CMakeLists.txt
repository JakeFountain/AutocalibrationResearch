##cmake_minimum_required(VERSION 2.6)
##project(NUGRAPICS)
##
##SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
##
##SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -O2 -Wpedantic -Wextra -Wall -Wno-unused-parameter -std=c++11" )
##
###There are lots of scripts with cmake
###for finding external libraries. 
###see /usr/local/share/cmake-2.6/Modules/Find*.cmake for more examples
##find_package(GLUT)
##find_package(OpenGL)
##find_package(GLM)
##find_package(GLFW)
##find_package(GLM)
##find_package(assimp)
##
##set(SOIL_INCLUDE_DIR /usr/local/include)
##set(SOIL_LIBRARY /usr/local/lib/libSOIL.a)
##
##INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR} REQUIRED)
##INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR} REQUIRED)
##INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR} REQUIRED)
##INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIR} REQUIRED)
##INCLUDE_DIRECTORIES(${GLM_INCLUDE_DIR} REQUIRED)
##INCLUDE_DIRECTORIES(${ASSIMP_INCLUDE_DIR} REQUIRED)
##INCLUDE_DIRECTORIES(${SOIL_INCLUDE_DIR} REQUIRED)
##
### TODO copy over shader folders
##
### Get our configuration files
##
##add_subdirectory(src)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(NUGRAPHICS_project)
SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 1)
SET(VERSION_PATCH 0)

# Tell CMake where to find our CMake modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_OSX_ARCHITECTURES "x86_64")

# Compiler settings
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -O0 -Wpedantic -Wextra -Wall -Wno-unused-parameter -std=c++11" )
ADD_DEFINITIONS(-DGLEW_STATIC)
ADD_DEFINITIONS(-DGLM_FORCE_RADIANS)
ADD_DEFINITIONS(-D_USE_MATH_DEFINES)

# Shared libraries
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)
FIND_PACKAGE(GLFW REQUIRED)
FIND_PACKAGE(GLM REQUIRED)
FIND_PACKAGE(GLUT REQUIRED)
FIND_PACKAGE(JPEG REQUIRED)
FIND_PACKAGE(PNG REQUIRED)
FIND_PACKAGE(png++ REQUIRED)
FIND_PACKAGE(Boost COMPONENTS system filesystem REQUIRED)
FIND_PACKAGE(assimp REQUIRED)
FIND_PACKAGE(armadillo REQUIRED)
FIND_PACKAGE(OPENCV REQUIRED)
FIND_PACKAGE(LIBUSB REQUIRED)

find_library(FOUNDATION Foundation)
find_library(AVFOUNDATION AVFoundation)
find_library(IOKIT IOKit)
find_library(COREFOUNDATION CoreFoundation)
find_library(IOBLUETOOTH IOBluetooth)
list(APPEND PSMOVEAPI_REQUIRED_LIBS ${FOUNDATION})
list(APPEND PSMOVEAPI_REQUIRED_LIBS ${AVFOUNDATION})
list(APPEND PSMOVEAPI_REQUIRED_LIBS ${IOKIT})
list(APPEND PSMOVEAPI_REQUIRED_LIBS ${COREFOUNDATION})
list(APPEND PSMOVEAPI_REQUIRED_LIBS ${IOBLUETOOTH})

message(PSMOVEAPI_REQUIRED_LIBS= ${PSMOVEAPI_REQUIRED_LIBS})

#psmove
set(PSMOVEAPI_INCLUDE_DIR /usr/local/psmoveapi/include)
set(PSMOVEAPI_LIBRARY #/usr/local/psmoveapi/lib64/libpsmoveapi.dylib
                      /usr/local/psmoveapi/lib64/libpsmoveapi_static.a
                      #/usr/local/psmoveapi/lib64/libpsmoveapi.3.1.0.dylib
    ) 
set(PSMOVEAPI_TRACKER_LIBRARY #/usr/local/psmoveapi/lib64/libpsmoveapi_tracker.dylib
                              /usr/local/psmoveapi/lib64/libpsmoveapi_tracker_static.a
                              #/usr/local/psmoveapi/lib64/libpsmoveapi_tracker.3.1.0.dylib
                              )

#soil image lib
set(SOIL_INCLUDE_DIR /usr/local/include)
set(SOIL_LIBRARY /usr/local/lib/libSOIL.a)

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR} REQUIRED)
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR} REQUIRED)
INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIR} REQUIRED)
INCLUDE_DIRECTORIES(${GLM_INCLUDE_DIR} REQUIRED)
INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR} REQUIRED)
INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIR} REQUIRED)
INCLUDE_DIRECTORIES(${PNG_INCLUDE_DIR} REQUIRED)
INCLUDE_DIRECTORIES(SYSTEM ${libpng++_INCLUDE_DIRS} REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR} REQUIRED)
INCLUDE_DIRECTORIES(${SOIL_INCLUDE_DIR} REQUIRED)
INCLUDE_DIRECTORIES(${ARMADILLO_INCLUDE_DIR} REQUIRED)
INCLUDE_DIRECTORIES(${LibUSB_INCLUDE_DIR} REQUIRED)
INCLUDE_DIRECTORIES(${ASSIMP_INCLUDE_DIR} REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIR} REQUIRED)
INCLUDE_DIRECTORIES(${PSMOVEAPI_INCLUDE_DIR} REQUIRED)
INCLUDE_DIRECTORIES(${PSMOVEAPI_TRACKER_INCLUDE_DIR} REQUIRED)


FILE(GLOB_RECURSE COMMON_SRC
      "common/**.cpp"
    )

set(COMMON_SRC  ${COMMON_SRC}
                utility/math/matrix/Transform3D.cpp
                utility/math/matrix/Rotation3D.cpp
                utility/math/geometry/UnitQuaternion.cpp)

INCLUDE_DIRECTORIES(".")
add_library(COMMON_LIB ${COMMON_SRC})
SET_PROPERTY(TARGET COMMON_LIB PROPERTY ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


set(LIBRARIES
    COMMON_LIB
    ${OPENGL_gl_LIBRARY}
    ${GLEW_LIBRARY}
    ${GLFW_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${JPEG_LIBRARIES}
    ${PNG_LIBRARIES}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${ASSIMP_LIBRARIES}
    ${SOIL_LIBRARY}
    ${LibUSB_LIBRARIES}
    ${OpenCV_LIBS}
    ${PSMOVEAPI_LIBRARY}
    ${PSMOVEAPI_TRACKER_LIBRARY}
    ${ARMADILLO_LIBRARY}
    ${PSMOVEAPI_REQUIRED_LIBS})

#Add subdirectories
FILE(GLOB EXECUTABLES
      "*"
    )
message(EXECUTABLES = ${EXECUTABLES})
foreach(CURRENT_FOLDER record view play)
  add_subdirectory(${CURRENT_FOLDER})
endforeach()
