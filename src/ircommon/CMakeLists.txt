project (ircommon
	VERSION 0.1)

# Fix the version strings
configure_file (
	${CMAKE_CURRENT_SOURCE_DIR}/include/ircommon/version.h.in
	${CMAKE_CURRENT_SOURCE_DIR}/include/ircommon/version.h
)
configure_file (
	${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
	${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
)

# Sources
add_library(ircommon STATIC 
	src/ilint.cpp
	src/iltag.cpp
	src/iralphab.cpp
	src/ircodec.cpp
	src/irbuffer.cpp
	src/irutils.cpp
	src/i32obfus.cpp
	src/irsemaph.cpp
	src/irrwlock.cpp
)
target_include_directories(ircommon PUBLIC
	include
	${OPENSSL_INCLUDE_DIR}
)

