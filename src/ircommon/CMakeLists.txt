project (ircommon
	VERSION 0.1)

# Fix the version strings
configure_file (
	include/ircommon/version.h.in
	include/ircommon/version.h
)
configure_file (
	Doxyfile.in
        Doxyfile
)

# Sources
add_library(ircommon STATIC 
	src/ilint.cpp
	src/iltag.cpp
	src/iralphab.cpp
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


