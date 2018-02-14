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
cmake_minimum_required (VERSION 3.9)
project (ircommon
	VERSION ${interlockrecord_VERSION})

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
	include/ircommon/irarc4.h
	include/ircommon/irbuffer.h
	include/ircommon/irjson.h
	include/ircommon/irsemaph.h
	include/ircommon/irfp.h
	include/ircommon/iralphab.h
	include/ircommon/iltag.h
	include/ircommon/iltagstd.h
	include/ircommon/irutils.h
	include/ircommon/ilint.h
	include/ircommon/version.h
	include/ircommon/ircodec.h
	include/ircommon/i32obfus.h
	include/ircommon/irrwlock.h
	include/ircommon/irpmem.h
	include/ircommon/irhndlst.h
	include/ircommon/iridgen.h
	src/irbuffer.cpp
	src/irutils.cpp
	src/irrwlock.cpp
	src/ircodec.cpp
	src/irsemaph.cpp
	src/iltag.cpp
	src/iralphab.cpp
	src/irpmem.cpp
	src/irarc4.cpp
	src/ilint.cpp
	src/irfp.cpp
	src/i32obfus.cpp
	src/iltagstd.cpp
	src/irjson.cpp
)

target_include_directories(ircommon 
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ircommon
	PUBLIC Threads::Threads
)

if(MSVC)
	target_link_libraries(ircommon
		PUBLIC Crypt32.lib
	)
endif()


