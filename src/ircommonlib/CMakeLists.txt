project (ircommonlib
	VERSION 0.1)

# Building the library
find_package(OpenSSL REQUIRED)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${OPENSSL_INCLUDE_DIR})

configure_file (
                "${CMAKE_CURRENT_SOURCE_DIR}/include/ircommon/version.h.in"
                "${CMAKE_CURRENT_SOURCE_DIR}/include/ircommon/version.h"
) 

add_library(ircommonlib STATIC 
	${CMAKE_CURRENT_SOURCE_DIR}/src/ilint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/iltag.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/irbuffer.cpp
)

msvc_set_static()

