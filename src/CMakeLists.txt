cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(ip_filter)

add_executable(ip_filter
			   main.cpp
			   hello.h
			   hello.cpp
)

target_compile_features(ip_filter PUBLIC cxx_std_14)
