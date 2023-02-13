# Command:
# cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release && cmake --build build && cmake --install build --prefix "." --config Release
# -S <path-to-source>          = Explicitly specify a source directory.
# -B <path-to-build>           = Explicitly specify a build directory.
# -G <generator-name>          = Specify a build system generator.
# -D <var>[:<type>]=<value>    = Create or update a cmake cache entry.
# --build <dir>                = Build a CMake-generated project binary tree.
# --install <dir>              = Install a CMake-generated project binary tree.
# 
# After running the command above, a 'bin/' folder will be created in the current directory because of --install and --prefix.

cmake_minimum_required(VERSION 3.20)
project(helloworld VERSION 0.0.1 LANGUAGES CXX)

add_executable(helloworld)

target_sources(helloworld PRIVATE helloworld.cpp Student.cpp Student.h)

install(TARGETS helloworld)
