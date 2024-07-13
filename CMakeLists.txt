cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(MyApp)

add_executable(MyApp
			   src/main.cpp
			   src/hello.h
			   src/hello.cpp
)

target_compile_features(MyApp PUBLIC cxx_std_11)