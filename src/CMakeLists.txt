cmake_minimum_required (VERSION 3.9)
project (interlockrecord)

# Including the global modules
set(MSVC_STATIC_CRT 1)
include("cmake/MSVCCRT.cmake")
include("cmake/Botan2.cmake")

# Sets the default output for all files
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Subprojects
add_subdirectory(ircommonlib)
add_subdirectory(ircommonlib-test)
add_subdirectory(irecord)
add_subdirectory(irecord-test)

