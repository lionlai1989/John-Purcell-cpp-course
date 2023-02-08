# Run `cmake -S . -B build -G Ninja && ninja -C build`

cmake_minimum_required(VERSION 3.16.3)
project(canonical_layout)
set(CMAKE_BUILD_TYPE Release)

add_subdirectory(src)
add_subdirectory(example)

target_include_directories(srclib PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(binrun PRIVATE ${CMAKE_SOURCE_DIR})
