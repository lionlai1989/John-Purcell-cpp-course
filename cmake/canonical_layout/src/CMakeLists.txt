file(GLOB SOURCES "*/*.cpp")

# Generate the shared library from the sources
add_library(srclib SHARED ${SOURCES})
