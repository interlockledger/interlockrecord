cmake_minimum_required (VERSION 3.7)
project (irecord-test
	VERSION 0.1)

enable_testing()
find_package(Threads)
find_package(GTest REQUIRED)
include_directories(
	${GTEST_INCLUDE_DIRS})
add_executable(irecord-tests
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	)
target_link_libraries(
	irecord-tests
	${GTEST_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT})

#include_directories(${CMAKE_SOURCE_DIR}/ircommonlib/include)
add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/irecord-tests)

