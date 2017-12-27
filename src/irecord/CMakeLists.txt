cmake_minimum_required(VERSION 3.9)
project (irecord
	VERSION 0.1.0.0)

# Fix the version strings
configure_file (
	src/version.h.in
	src/version.h
)
configure_file (
	Doxyfile.in
	Doxyfile
)

# Sources
add_library(irecord SHARED
	src/IRGetVersion.cpp
)
target_include_directories(irecord PUBLIC 
	include
)
target_compile_definitions(irecord
	PUBLIC IR_EXPORTS
)
