# Run `cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug && ninja -C build`

cmake_minimum_required(VERSION 3.20)
project(canonical_layout VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(example)

target_include_directories(srclib PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(binrun PRIVATE ${CMAKE_SOURCE_DIR})
