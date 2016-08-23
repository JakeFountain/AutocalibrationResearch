# Find our globally shared libraries:
FIND_PACKAGE(NUClear REQUIRED)
FIND_PACKAGE(armadillo REQUIRED)
FIND_PACKAGE(Protobuf REQUIRED)
FIND_PACKAGE(CATCH REQUIRED)
FIND_PACKAGE(YAML-CPP REQUIRED)
FIND_PACKAGE(muParser REQUIRED)
FIND_PACKAGE(CPPFormat REQUIRED)
# FIND_PACKAGE(OpenBLAS REQUIRED)
# FIND_PACKAGE(BLAS REQUIRED)
# message( OpenBLAS_INCLUDE_DIRS ${OpenBLAS_INCLUDE_DIRS})
# message( OpenBLAS_LIBRARY ${OpenBLAS_LIBRARY})
# SET(BLAS_INCLUDE_DIRS OpenBLAS_INCLUDE_DIRS)
# SET(BLAS_INCLUDE_DIR OpenBLAS_INCLUDE_DIRS)
# SET(BLAS_LIBRARY OpenBLAS_LIBRARY)
# FIND_PACKAGE(LAPACK REQUIRED)
FIND_PACKAGE(OpenNI2 REQUIRED)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)

#PSMOVE AND GRAPHICS
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
FIND_PACKAGE(OPENCV REQUIRED)
FIND_PACKAGE(LIBUSB REQUIRED)
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics audio REQUIRED)
FIND_PACKAGE(NITE REQUIRED)

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


# Set include directories and libraries:
INCLUDE_DIRECTORIES(SYSTEM ${NUClear_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${BLAS_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${PROTOBUF_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${CATCH_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${YAML-CPP_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${muParser_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${CPPFormat_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${OPENNI2_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${ARMADILLO_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${NITE_INCLUDE_DIRS})

FILE(COPY /usr/local/lib64/NiTE2/NiTE2 DESTINATION ${CMAKE_BINARY_DIR})
MESSAGE("COPIED /usr/local/lib64/NiTE2/NiTE2 TO DESTINATION ${CMAKE_BINARY_DIR}")

#PSMOVE AND GRAPHICS

#psmove
set(PSMOVEAPI_INCLUDE_DIR /usr/local/include)
set(PSMOVEAPI_LIBRARY #/usr/local/lib64/libpsmoveapi.dylib
                      /usr/local/lib64/libpsmoveapi_static.a
                      #/usr/local/lib64/libpsmoveapi.3.1.0.dylib
    ) 
set(PSMOVEAPI_TRACKER_LIBRARY #/usr/local/lib64/libpsmoveapi_tracker.dylib
                              /usr/local/lib64/libpsmoveapi_tracker_static.a
                              #/usr/local/lib64/libpsmoveapi_tracker.3.1.0.dylib
                              )

#soil image lib
set(SOIL_INCLUDE_DIR /usr/local/include)
set(SOIL_LIBRARY /usr/local/lib/libSOIL.a)

# message(ASSIMP_LIBRARIES ${ASSIMP_LIBRARIES})


INCLUDE_DIRECTORIES(SYSTEM ${OPENGL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${SFML_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${GLEW_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${GLFW_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${GLM_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${GLUT_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${JPEG_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${PNG_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${libpng++_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(SYSTEM ${Boost_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${SOIL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${LibUSB_INCLUDE_DIR})
# INCLUDE_DIRECTORIES(SYSTEM ${ASSIMP_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${OpenCV_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${PSMOVEAPI_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${PSMOVEAPI_TRACKER_INCLUDE_DIR})
INCLUDE_DIRECTORIES(SYSTEM ${OpenBLAS_INCLUDE_DIRS})


SET(NUCLEAR_ADDITIONAL_SHARED_LIBRARIES
    ${NUClear_LIBRARIES}
    ${OpenBLAS_LIBRARIES}
    # ${BLAS_LIBRARIES}
    -lblas
    -llapack
    ${LIBGFORTRAN_LIBRARIES}
    ${PROTOBUF_LIBRARIES}
    ${YAML-CPP_LIBRARIES}
    ${muParser_LIBRARIES}
    ${CPPFormat_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    ${GLEW_LIBRARY}
    ${GLFW_LIBRARIES}
    ${SFML_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${JPEG_LIBRARIES}
    ${PNG_LIBRARIES}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    # ${ASSIMP_LIBRARIES}
    ${SOIL_LIBRARY}
    ${LibUSB_LIBRARIES}
    ${OpenCV_LIBS}
    ${PSMOVEAPI_LIBRARY}
    ${PSMOVEAPI_TRACKER_LIBRARY}
    ${ARMADILLO_LIBRARY}
    ${PSMOVEAPI_REQUIRED_LIBS}
    ${OPENNI2_LIBRARIES}
    ${NITE_LIBRARIES}
)
