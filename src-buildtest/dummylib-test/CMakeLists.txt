cmake_minimum_required (VERSION 3.7)
project (dummylib-test
	VERSION 0.1)

enable_testing()

add_executable(dummylib-test
	src/dummylibtest.cpp
	src/main.cpp)

target_include_directories(dummylib-test 
	PUBLIC dummylib)

target_link_libraries(dummylib-test
	dummylib
	GTest)

add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dummylib-tests)

