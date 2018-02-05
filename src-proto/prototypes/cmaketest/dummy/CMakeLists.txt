cmake_minimum_required (VERSION 3.7)
project (dummy
	VERSION 0.1)

add_executable(dummy
	src/main.cpp)

target_include_directories(dummylib-test 
	PUBLIC dummylib)

target_link_libraries(dummy
	dummylib
	${GTEST_LIBRARIES})

