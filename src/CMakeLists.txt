cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
project (scif-perf-bench)

add_subdirectory (primitives)
include_directories (primitives)

set (CMAKE_CXX_FLAGS "-std=c++0x -Wall")
set (CMAKE_CXX_FLAGS "-std=c++0x -Wall")

set_source_files_properties (source.cpp PROPERTIES COMPILE_FLAGS  "-mmic")

add_executable (source source.cpp)
add_executable (sink sink.cpp)

set_target_properties (source PROPERTIES LINK_FLAGS "-mmic")

target_link_libraries (source primitives_sender scif pthread)
target_link_libraries (sink primitives_receiver scif pthread)

install (TARGETS source sink DESTINATION bin/)