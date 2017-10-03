cmake_minimum_required (VERSION 3.7)
project (ircommon
	VERSION 0.1)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(ircommon STATIC 
	${CMAKE_CURRENT_SOURCE_DIR}/src/ilint.cpp
)

