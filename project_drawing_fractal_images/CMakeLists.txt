# Steps to complie and run:
# cmake -B build .
# cd build
# make
# ./runfractalimage
# Or do something like:
# mkdir build && cd build
# cmake .. && make && ./runfractalimage

cmake_minimum_required(VERSION 3.16.3)
project (Fractal_Image)
 
include_directories(include)
 
file(GLOB SOURCES "src/*.cpp")
 
add_executable(runfractalimage ${SOURCES})
