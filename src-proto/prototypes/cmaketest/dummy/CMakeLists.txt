cmake_minimum_required (VERSION 3.7)
project (dummy
	VERSION 0.1)

add_executable(dummy
	src/main.cpp)

target_include_directories(dummylib-test 
	PUBLIC 
	$<TARGET_PROPERTY:dummylib,INTERFACE_INCLUDE_DIRECTORIES>)

target_link_libraries(dummy
	dummylib
	${GTEST_LIBRARIES})

