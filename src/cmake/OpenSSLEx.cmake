
# Find OpenSSL
find_package(OpenSSL REQUIRED)
# Patch the variable OPENSSL_INCLUDE_DIR on Windows in order to avoid problems with the
# header and binaries.
if (WIN32)
	find_path(OPENSSL_INCLUDE_DIR_ALT
	  NAMES
		openssl/ssl.h
	  NO_DEFAULT_PATH	
	  PATHS
		${_OPENSSL_ROOT_PATHS}
	  PATH_SUFFIXES
		include
	)
	set(OPENSSL_INCLUDE_DIR "${OPENSSL_INCLUDE_DIR_ALT}")
endif()
