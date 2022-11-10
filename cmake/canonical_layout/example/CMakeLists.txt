add_executable(binrun run.cpp)

target_link_libraries(binrun PRIVATE srclib)

SET_TARGET_PROPERTIES(binrun PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
