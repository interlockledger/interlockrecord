cmake_minimum_required(VERSION 3.9)
project (irecordcore
	VERSION 0.1)

# Fix the version strings
configure_file (
	${CMAKE_CURRENT_SOURCE_DIR}/include/irecordcore/version.h.in
	${CMAKE_CURRENT_SOURCE_DIR}/include/irecordcore/version.h
)
configure_file (
	${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
	${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
)

# Sources
add_library(irecordcore STATIC
	src/irtags.cpp
	src/irhash.cpp
	src/IRCHandle.cpp)
	
target_include_directories(irecordcore PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${BOTAN2_INCLUDE_DIR}
	ircommon	
)

target_link_libraries(irecordcore
	PUBLIC ircommon
	PUBLIC Botan2
)
