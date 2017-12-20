cmake_minimum_required (VERSION 3.7)
project (irecord-test
	VERSION 0.1)

enable_testing()
find_package(Threads)
find_package(GTest REQUIRED)
add_executable(irecord-tests
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRGetVersionTest.cpp
	)
target_include_directories(irecord-tests PUBLIC
	irecord
	"${GTEST_INCLUDE_DIRS}"
)
target_link_libraries(
	irecord-tests
	irecord
	${GTEST_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT})

add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/irecord-tests)


