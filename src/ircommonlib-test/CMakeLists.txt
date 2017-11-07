cmake_minimum_required (VERSION 3.7)
project (ircommonlib-test
	VERSION 0.1)

enable_testing()
find_package(Threads)
find_package(GTest REQUIRED)
include_directories(
	${CMAKE_SOURCE_DIR}/include
	${GTEST_INCLUDE_DIRS})
add_executable(ircommonlib-tests
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ILIntTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRBufferTest.cpp
	)
target_link_libraries(
	ircommonlib-tests
	ircommonlib
	${GTEST_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
	ircommonlib)
include_directories(${CMAKE_SOURCE_DIR}/ircommonlib/include)
add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ircommon-tests)

msvc_set_static ()

