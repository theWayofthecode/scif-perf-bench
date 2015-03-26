cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
project (scif-perf-bench)

add_subdirectory (primitives)
include_directories (primitives)

set (CMAKE_CXX_FLAGS "-std=c++0x -Wall $ENV{CXX_FLAGS}")

add_executable ("source.$ENV{ARCH}" source.cpp)
add_executable ("sink.$ENV{ARCH}" sink.cpp)

target_link_libraries (source.$ENV{ARCH} primitives_sender scif pthread)
target_link_libraries (sink.$ENV{ARCH} primitives_receiver scif pthread)

install (TARGETS source.$ENV{ARCH} sink.$ENV{ARCH} DESTINATION bin/)