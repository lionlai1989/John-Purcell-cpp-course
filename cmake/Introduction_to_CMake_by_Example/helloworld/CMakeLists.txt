# Command:
# cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug && ninja -C build

cmake_minimum_required(VERSION 3.20)
project(helloworld VERSION 0.0.1 LANGUAGES CXX)

add_executable(helloworld helloworld.cpp)
