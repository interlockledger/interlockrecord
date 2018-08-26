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
project (interlockrecord
	VERSION 0.1.0.0)

# Set the requirement to C++11 - Required for old gcc compilers
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_STANDARD 11)

# Including the global modules
set(MSVC_STATIC_CRT 1)
include("cmake/MSVCCRT.cmake")

# GTest
set(GTEST_VERBOSE 1)
include("cmake/GTest.cmake")

# Botan2
set(BOTAN2_VERBOSE 1)
include("cmake/Botan2.cmake")

# Warnings on GCC
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall") 
	set (CMAKE_CFLAGS_DEBUG "${CMAKE_CFLAGS_DEBUG} -Wall") 
endif()

# Threads
find_package(Threads REQUIRED)
if (CMAKE_USE_PTHREADS_INIT)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

# Sets the default output for all files
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Subprojects
add_subdirectory(ircommon)
add_subdirectory(ircommon-test)
add_subdirectory(irecordcore)
add_subdirectory(irecordcore-test)
add_subdirectory(irecord)
add_subdirectory(irecord-test)

