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
# ==============================================================================
# This module locates the Botan2 library in the sysyem.
#
# Targets:
#
#    - Botan2
#
# Variables
#
#    - BOTAN2_LIB
#    - BOTAN2D_LIB
#    - BOTAN2_INCLUDE_DIR
#    - BOTAN2_VERSION
#    - BOTAN2_FOUND
#
# This method depends on MSVCCRT from OpenCS in order to work properly.
#
# History:
#    - 2018.02.14: Support to "-dbg" libraries on Linux added;
#
# Known limitations:
# 	- This version of the module was not tested on MacOS.
if(__OPENCS_BOTAN2)
  return()
endif()
set(__OPENCS_BOTAN2 1)

# Botan2 options
option(BOTAN2_USE_STATIC "Use botan2 static library." 0)
# option(BOTAN2_VERBOSE "Use botan2 static library." 0)

# Check the dependency on 
if (NOT __OPENCS_MSVCCRT)
	message(FATAL_ERROR "OpenCS Botan2 module requires OpenCS MSVCCRT module in order to work properly.")
endif()

function(botan2_log _msg)
	if (BOTAN2_VERBOSE)
		message(STATUS ${_msg})
	endif()
endfunction()

if (WIN32)
	if(NOT DEFINED MSVC_CRT_FLAG)
		set(MSVC_CRT_FLAG "MD")
	endif()
	
	# Get from ENV
	if(NOT "$ENV{BOTAN2_HOME}" STREQUAL "") 
		set(_BOTAN_CANDIDATE_PATHS "$ENV{BOTAN2_HOME}")
		botan2_log("Using Botan2 location defined by BOTAN2_HOME.")
	elseif(NOT "$ENV{BOTAN2_DIR}" STREQUAL "") 
		set(_BOTAN_CANDIDATE_PATHS "$ENV{BOTAN2_DIR}")
		botan2_log("Using Botan2 location defined by BOTAN2_DIR.")
	else()
		botan2_log("Looking Botan2 location inside <drive>:\\botan")
		foreach(_botan_dir a b c d e f g h i j k l m n o p q r s t u v w x y z)
			set(_BOTAN_CANDIDATE_PATHS
				${_BOTAN_CANDIDATE_PATHS}
				"${_botan_dir}:/botan"
				)
		endforeach()
	endif()
	
	find_library(BOTAN2_LIB
		"botan-${MSVC_CRT_FLAG}.lib"
		PATHS ${_BOTAN_CANDIDATE_PATHS}
		PATH_SUFFIXES "${WIN32_TARGET_PLATFORM}/lib")
	
	find_library(BOTAN2D_LIB
		"botand-${MSVC_CRT_FLAG}.lib"
		PATHS ${_BOTAN_CANDIDATE_PATHS}
		PATH_SUFFIXES "${WIN32_TARGET_PLATFORM}/lib")
		
	find_path(BOTAN2_INCLUDE_DIR
		"botan/botan.h"
		PATHS ${_BOTAN_CANDIDATE_PATHS}
		PATH_SUFFIXES 
			"${WIN32_TARGET_PLATFORM}/include/botan-2")
	set(BOTAN2_DEPS Ws2_32.lib)
else()
	# Linux and other
	find_library(BOTAN2_STATIC_LIB
		"libbotan-2.a")
	find_library(BOTAN2_SHARED_LIB
		"libbotan-2.so")

	#
	if(BOTAN2_USE_STATIC)
		set(BOTAN2_LIB ${BOTAN2_STATIC_LIB})
	else()
		set(BOTAN2_LIB ${BOTAN2_SHARED_LIB})
	endif()

	find_path(BOTAN2_INCLUDE_DIR
		"botan/botan.h"
		PATH_SUFFIXES "botan-2")
	find_library(BOTAN2D_LIB
		"libbotan-2-dbg.a")
	if(NOT BOTAN2D_LIB)
		set(BOTAN2D_LIB "${BOTAN2_LIB}")
	endif()
endif()

if(DEFINED BOTAN2_INCLUDE_DIR)
	botan2_log("Botan2 headers found in ${BOTAN2_INCLUDE_DIR}.")
	
	# Extract the Botan version from build.h
	if(EXISTS "${BOTAN2_INCLUDE_DIR}/botan/build.h")
		file(STRINGS "${BOTAN2_INCLUDE_DIR}/botan/build.h" _BOTAN2_BUILD_HEADER)
		string(REGEX REPLACE ".+BOTAN_VERSION_MAJOR ([0-9]+).+BOTAN_VERSION_MINOR ([0-9]+).+BOTAN_VERSION_PATCH ([0-9]+).+" 
			"\\1.\\2.\\3" BOTAN2_VERSION "${_BOTAN2_BUILD_HEADER}")
		unset(_BOTAN2_BUILD_HEADER)
	else()
		set(BOTAN2_VERSION "0.0.0")
	endif()
	botan2_log("Botan2 version is ${BOTAN2_VERSION}")

	# Define the library
	if(NOT TARGET Botan2)
		add_library(Botan2 UNKNOWN IMPORTED)
		set_target_properties(Botan2 PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${BOTAN2_INCLUDE_DIR}")
		if(BOTAN2_LIB)
			set_property(TARGET Botan2 APPEND PROPERTY
				IMPORTED_CONFIGURATIONS RELEASE)
			set_target_properties(Botan2 PROPERTIES
				IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
				IMPORTED_LOCATION_RELEASE "${BOTAN2_LIB}")
			botan2_log("Botan2 release lib found at ${BOTAN2_LIB}")
		endif()
		if(BOTAN2D_LIB)
			set_property(TARGET Botan2 APPEND PROPERTY
				IMPORTED_CONFIGURATIONS DEBUG)
			set_target_properties(Botan2 PROPERTIES
				IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
				IMPORTED_LOCATION_DEBUG "${BOTAN2D_LIB}")
			botan2_log("Botan2 debug lib found at ${BOTAN2D_LIB}")
		endif()
		if(BOTAN2_DEPS)
			set_target_properties(Botan2 PROPERTIES
				INTERFACE_LINK_LIBRARIES "${BOTAN2_DEPS}")
			botan2_log("Botan2 requires the following additional libraries: ${BOTAN2_DEPS}")
		endif()
	endif()		
	set(BOTAN2_FOUND 1)
endif()
