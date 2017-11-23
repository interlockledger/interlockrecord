cmake_minimum_required (VERSION 3.9)
project (interlockrecord)

include("cmake/MSVCUtils.cmake")
include("cmake/OpenSSLEx.cmake")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	
add_subdirectory(ircommonlib)
add_subdirectory(ircommonlib-test)
