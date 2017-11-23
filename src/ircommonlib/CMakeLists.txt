project (ircommonlib
	VERSION 0.1)

# Fix the version strings
configure_file (
                "${CMAKE_CURRENT_SOURCE_DIR}/include/ircommon/version.h.in"
                "${CMAKE_CURRENT_SOURCE_DIR}/include/ircommon/version.h"
)
configure_file (
                "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
                "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile"
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${OPENSSL_INCLUDE_DIR})

# Sources
add_library(ircommonlib STATIC 
	${CMAKE_CURRENT_SOURCE_DIR}/src/ilint.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/iltag.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/irbuffer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/irutils.cpp
)

# Force the static build with MSVC
msvc_set_static()

