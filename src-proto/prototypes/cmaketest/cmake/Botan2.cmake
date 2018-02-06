# Copyright (c) 2017-2018, Open Communications Security
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the <organization> nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL OPEN COMMUNICATIONS SECURITY BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# This module locates Botan2 and defines the external library Botan2 on success.
#
# It also defines the following constants:
#    - BOTAN2_LIB: The Botan 2 library;
#    - BOTAN2D_LIB: The Botan 2 library for debug;
#    - BOTAN2_INCLUDE_DIR: The Botan 2 include library;
#    - BOTAN2_VERSION: The version of the Botan library extracted from "build.h";
#    - BOTAN2_FOUND: Flag that indicates that the Botan2 library was found;
#
# This method depends on MSVCCRT from OpenCS in order to work properly.
#
# Known limitations:
# 	- This version of the module was not tested on MacOS.
if(__OPENCS_BOTAN2)
  return()
endif()
set(__OPENCS_BOTAN2 1)

# Check the dependency on 
if (NOT __OPENCS_MSVCCRT)
	message(FATAL_ERROR "OpenCS Botan2 module requires OpenCS MSVCCRT module in order to work properly.")
endif()

if (WIN32)
	if(CMAKE_CL_64)
		set(platform "x64")
	else()
		set(platform "x86")
	endif()

	if(NOT DEFINED MSVC_CRT_FLAG)
		set(MSVC_CRT_FLAG "MD")
	endif()

	set(_BOTAN_CANDIDATE_PATHS
		"c:/botan"
		"d:/botan"
		"e:/botan")
	find_library(BOTAN2_LIB
		"botan-${MSVC_CRT_FLAG}.lib"
		PATHS ${_BOTAN_CANDIDATE_PATHS}
		PATH_SUFFIXES "lib/${platform}")
	find_library(BOTAN2D_LIB
		"botan-${MSVC_CRT_FLAG}d.lib"
		PATHS ${_BOTAN_CANDIDATE_PATHS}
		PATH_SUFFIXES "lib/${platform}")
	find_path(BOTAN2_INCLUDE_DIR
		"botan/botan.h"
		PATHS ${_BOTAN_CANDIDATE_PATHS}
		PATH_SUFFIXES 
			"include/botan-2"
			"botan-2")
	set(BOTAN2_DEPS Ws2_32.lib)
else()
	# Linux and other
	find_library(BOTAN2_LIB
		"libbotan-2.a")
	find_library(BOTAN2_SHARED_LIB
		"libbotan-2.so")
	find_path(BOTAN2_INCLUDE_DIR
		"botan/botan.h"
		PATH_SUFFIXES "botan-2")
	# TODO Fix this dependency later
	set(BOTAN2D_LIB "${BOTAN2_LIB}")
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
		set(BOTAN2_FOUND 1)
		message(STATUS "Botan ${BOTAN2_VERSION} found.")
		
		# Define the library
		if(NOT TARGET Botan2)
			add_library(Botan2 UNKNOWN IMPORTED)
			set_target_properties(Botan2 PROPERTIES
				INTERFACE_INCLUDE_DIRECTORIES "${BOTAN2_INCLUDE_DIR}")
			if(DEFINED BOTAN2_DEPS)
				set_target_properties(Botan2 PROPERTIES
					INTERFACE_LINK_LIBRARIES "${BOTAN2_DEPS}")
			endif()
            set_property(TARGET Botan2 APPEND PROPERTY
				IMPORTED_CONFIGURATIONS RELEASE)
            set_target_properties(Botan2 PROPERTIES
				IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
				IMPORTED_LOCATION_RELEASE "${BOTAN2_LIB}")
            set_property(TARGET Botan2 APPEND PROPERTY
                IMPORTED_CONFIGURATIONS DEBUG)
            set_target_properties(Botan2 PROPERTIES
                IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
                IMPORTED_LOCATION_DEBUG "${BOTAN2D_LIB}")
		endif()		
	endif()
endif()

