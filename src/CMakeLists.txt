cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(ip_filter)

#include files of project
add_executable(ip_filter
			   main.cpp
			   hello.h
			   hello.cpp
)

#include tests
#add_executable(
#	name
#	source
#)

target_compile_features(ip_filter PUBLIC cxx_std_14)
