cmake_minimum_required (VERSION 3.7)
project (ircommon
	VERSION 0.1)

macro(msvc_set_static)
	# Force the build with a static copy of the CRT
	if (MSVC)
		foreach (flag_var
				 CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
				 CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
			string(REPLACE "/MD" "-MT" ${flag_var} "${${flag_var}}")
		endforeach()
	endif()	
endmacro()	
	
# Building the library
include_directories(${CMAKE_SOURCE_DIR}/include)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

configure_file (
                "${CMAKE_SOURCE_DIR}/include/ircommon/version.h.in"
                "${CMAKE_SOURCE_DIR}/include/ircommon/version.h"
) 

add_library(ircommon STATIC 
	${CMAKE_SOURCE_DIR}/src/ilint.cpp
	${CMAKE_SOURCE_DIR}/src/iltag.cpp
)

msvc_set_static ()

# Unit test program
enable_testing()
find_package(Threads)
find_package(GTest REQUIRED)
include_directories(
	${CMAKE_SOURCE_DIR}/include
	${GTEST_INCLUDE_DIRS})
add_executable(ircommon-tests
	${CMAKE_SOURCE_DIR}/test/main.cpp
	${CMAKE_SOURCE_DIR}/test/ILIntTest.cpp)
target_link_libraries(ircommon-tests
	${GTEST_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
	ircommon)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ircommon-tests)

