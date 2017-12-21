cmake_minimum_required(VERSION 3.9)
project (irecordcore
	VERSION 0.1)

# Fix the version strings
configure_file (
	include/irecordcore/version.h.in
	include/irecordcore/version.h
)
configure_file (
	Doxyfile.in
        Doxyfile
)

# Sources
add_library(irecordcore STATIC
	src/IRCHandle.cpp)
target_include_directories(irecordcore PUBLIC
	include
	ircommonlib
)

