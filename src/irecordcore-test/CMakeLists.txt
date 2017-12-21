cmake_minimum_required (VERSION 3.7)
project (irecordcore-test
	VERSION 0.1)

enable_testing()
find_package(Threads)
find_package(GTest REQUIRED)
add_executable(irecordcore-test
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(irecordcore-test PUBLIC
	irecordcore
	"${GTEST_INCLUDE_DIRS}"
)
target_link_libraries(irecordcore-test
	irecord
	irecordcore
	${GTEST_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
)
add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/irecordcore-test)

