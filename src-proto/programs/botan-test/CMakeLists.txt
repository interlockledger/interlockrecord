cmake_minimum_required(VERSION 3.9)
project(botan-test)

include("Botan2.cmake")

add_executable(botan-test
	test.cpp)
target_include_directories(botan-test
	 PRIVATE "${BOTAN2_INCLUDE_DIR}")
target_link_libraries(botan-test
	"${BOTAN2_LIB}")
