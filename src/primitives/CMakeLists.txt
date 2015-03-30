cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
project (scif-perf-bench)

set (CMAKE_CXX_FLAGS "-std=c++0x -Wall $ENV{CXX_FLAGS}")

set (PRIMITIVES_SENDER_FILES
	MSGSender.cpp
	VwritetoSender.cpp
	WritetoSender.cpp
	RMASender.cpp)

set (PRIMITIVES_RECEIVER_FILES
	MSGReceiver.cpp
	RMAReceiver.cpp
	ReadfromReceiver.cpp)

add_library(primitives_sender ${PRIMITIVES_SENDER_FILES})
add_library(primitives_receiver ${PRIMITIVES_RECEIVER_FILES})
