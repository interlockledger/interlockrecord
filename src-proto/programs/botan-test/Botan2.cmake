# Locate the Botan components
if (WIN32)
	set(_BOTAN_HINTS
		"c:/botan")
	find_library(BOTAN2_LIB
		"botan-mt.lib"
		PATHS ${_BOTAN_HINTS}
		PATH_SUFFIXES "lib/x64")
	find_path(BOTAN2_INCLUDE_DIR
		"botan/botan.h"
		PATHS ${_BOTAN_HINTS}
		PATH_SUFFIXES 
			"include/botan-2"
			"botan-2")
else()
	find_library(BOTAN2_LIB
		"libbotan-2.a")
	find_library(BOTAN2_SHARED_LIB
		"libbotan-2.so")
	find_path(BOTAN2_INCLUDE_DIR
		"botan/botan.h"
		PATH_SUFFIXES "botan-2")
endif()

# Extract the Botan version from build.h
if(EXISTS "${BOTAN2_INCLUDE_DIR}/botan/build.h")
	file(STRINGS "${BOTAN2_INCLUDE_DIR}/botan/build.h" _BOTAN2_BUILD_HEADER)
	string(REGEX REPLACE ".+BOTAN_VERSION_MAJOR ([0-9]+).+BOTAN_VERSION_MINOR ([0-9]+).+BOTAN_VERSION_PATCH ([0-9]+).+" 
		"\\1.\\2.\\3" BOTAN2_VERSION "${_BOTAN2_BUILD_HEADER}")
	unset(_BOTAN2_BUILD_HEADER)
else()
	set(BOTAN2_VERSION "0.0.0")
endif()

if(DEFINED BOTAN2_LIB)
	if(DEFINED BOTAN2_INCLUDE_DIR)
		set(BOTAN2_FOUND "${BOTAN2_VERSION}")
		message(STATUS "Botan ${BOTAN2_VERSION} found.")
	endif()
endif()

