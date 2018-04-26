cmake_minimum_required(VERSION 3.9)
project(json-test
	VERSION 1.2.3.4)

#-------------------------------------------------------------------------------
# Building the loader
add_executable(json-test
	main.cpp
	irjson.cpp)

