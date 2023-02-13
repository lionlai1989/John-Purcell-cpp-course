# Please read https://iamsorush.com/posts/cpp-cmake-build/ for more insights.
#
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
project(student VERSION 0.0.1 LANGUAGES CXX)

# Do not use include_directories(), which is deprecated.

# Do not use the following method to add source files. It's wrong.
# file(GLOB SOURCES "src/*.cpp")

add_executable(mainapp)

# PROJECT_SOURCE_DIR: The source directory of the most recent call to project()
# in the current scope or any parent scope. The name of the project (i.e. the
# first argument given to the project() command) is not relevant. 
target_include_directories(mainapp PRIVATE "${PROJECT_SOURCE_DIR}")

add_subdirectory("src")

target_sources(mainapp PRIVATE "mainapp.cpp")

install(TARGETS mainapp)
