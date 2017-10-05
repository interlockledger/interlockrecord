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


# Unit test program
enable_testing()
find_package(Threads)
find_package(GTest REQUIRED)
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${GTEST_INCLUDE_DIRS})
add_executable(ircommon-tests
	${CMAKE_BINARY_DIR}/test/main.cpp
	${CMAKE_BINARY_DIR}/test/ILIntTest.cpp)
target_link_libraries(ircommon-tests
	${GTEST_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
	ircommon)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ircommon-tests)

