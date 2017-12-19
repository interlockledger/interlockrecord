cmake_minimum_required(VERSION 3.9)
project (irecord
	VERSION 0.1.0.0)

# Fix the version strings
configure_file (
                "${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in"
                "${CMAKE_CURRENT_SOURCE_DIR}/src/version.h"
)
configure_file (
                "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
                "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile"
)

set(irecord_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories(
	"${irecord_INCLUDE}"
)

# Sources
add_library(irecord SHARED
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRGetVersion.cpp
)
target_compile_definitions(irecord
	PUBLIC IR_EXPORTS
)

