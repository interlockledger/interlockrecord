project (irecordcore
	VERSION 0.1)

# Fix the version strings
configure_file (
	include/irecordcore/version.h.in
	include/irecordcore/version.h
)
configure_file (
	Doxyfile.in
        Doxyfile
)

# Sources
#add_library(irecordcore STATIC)
#target_include_directories(irecordcore PUBLIC
#	include
#	ircommonlib
#	${OPENSSL_INCLUDE_DIR}
#)

