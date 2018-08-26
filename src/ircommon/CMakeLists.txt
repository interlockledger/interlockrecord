# Copyright (c) 2017-2018 InterlockLedger Network
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

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
	include/ircommon/i32obfus.h
	include/ircommon/ilint.h
	include/ircommon/iltag.h
	include/ircommon/iltagstd.h
	include/ircommon/iralphab.h
	include/ircommon/irarc4.h
	include/ircommon/irbuffer.h
	include/ircommon/ircodec.h
	include/ircommon/irfp.h
	include/ircommon/irhndlst.h
	include/ircommon/iridgen.h
	include/ircommon/irjson.h
	include/ircommon/irpmem.h
	include/ircommon/irrandom.h
	include/ircommon/irrwlock.h
	include/ircommon/irsemaph.h
	include/ircommon/irshrand.h
	include/ircommon/irutils.h
	include/ircommon/version.h
	src/i32obfus.cpp
	src/ilint.cpp
	src/iltag.cpp
	src/iltagstd.cpp
	src/iralphab.cpp
	src/irarc4.cpp
	src/irbuffer.cpp
	src/ircodec.cpp
	src/irfp.cpp
	src/irjson.cpp
	src/irpmem.cpp
	src/irrandom.cpp
	src/irrwlock.cpp
	src/irsemaph.cpp
	src/irshrand.cpp
	src/irutils.cpp
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


