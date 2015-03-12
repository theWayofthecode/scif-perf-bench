cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
project (scif-perf-bench)

set (CMAKE_CXX_FLAGS "-std=c++0x -Wall")
set (CMAKE_CXX_FLAGS "-std=c++0x -Wall")

set (PRIMITIVES_SENDER_FILES
	MSGSender.cpp
	VwritetoSender.cpp
	WritetoSender.cpp)

set (PRIMITIVES_RECEIVER_FILES
	MSGReceiver.cpp
	RMAReceiver.cpp)

set_source_files_properties(${PRIMITIVES_SENDER_FILES} PROPERTIES COMPILE_FLAGS  "-mmic")

add_library(primitives_sender ${PRIMITIVES_SENDER_FILES})
add_library(primitives_receiver ${PRIMITIVES_RECEIVER_FILES})

set_target_properties (primitives_sender PROPERTIES LINK_FLAGS "-mmic")
