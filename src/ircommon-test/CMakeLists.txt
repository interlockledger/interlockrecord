cmake_minimum_required (VERSION 3.7)
project (ircommon-test
	VERSION 0.1)

enable_testing()
find_package(GTest REQUIRED)
add_executable(ircommon-test
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ILIntTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRBufferTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRUtilsTest.cpp)

target_include_directories(ircommon-test PUBLIC
	ircommon
	${GTEST_INCLUDE_DIRS})
target_link_libraries(ircommon-test
	ircommon
	${GTEST_LIBRARIES})

include_directories(${CMAKE_SOURCE_DIR}/ircommon/include)

add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ircommon-tests)

