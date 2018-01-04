cmake_minimum_required (VERSION 3.9)
project (interlockrecord)

# Including the global modules
set(MSVC_STATIC_CRT 1)
include("cmake/MSVCCRT.cmake")
include("cmake/Botan2.cmake")

# Threads
find_package(Threads)
if (CMAKE_USE_PTHREADS_INIT)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

# Sets the default output for all files
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Subprojects
add_subdirectory(ircommon)
add_subdirectory(ircommon-test)
add_subdirectory(irecordcore)
add_subdirectory(irecordcore-test)
add_subdirectory(irecord)
add_subdirectory(irecord-test)

