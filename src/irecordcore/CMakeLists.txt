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
cmake_minimum_required(VERSION 3.9)
project (irecordcore
	VERSION ${interlockrecord_VERSION})

# Fix the version strings
configure_file (
	${CMAKE_CURRENT_SOURCE_DIR}/include/irecordcore/version.h.in
	${CMAKE_CURRENT_SOURCE_DIR}/include/irecordcore/version.h
)
configure_file (
	${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
	${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
)

# Sources
add_library(irecordcore STATIC
	include/irecordcore/irblock.h
	include/irecordcore/IRCHandle.h
	include/irecordcore/irbciphm.h
	include/irecordcore/ircipher.h
	include/irecordcore/irciphpd.h
	include/irecordcore/ircrypto.h
	include/irecordcore/irhash.h
	include/irecordcore/irkeygen.h
	include/irecordcore/irkey.h
	include/irecordcore/irmac.h
	include/irecordcore/irpayload.h
	include/irecordcore/irpbkdf2.h
	include/irecordcore/irsrand.h
	include/irecordcore/irtags.h
	include/irecordcore/irtypes.h
	include/irecordcore/version.h
	src/irblock.cpp
	src/IRCHandle.cpp
	src/irbciphm.cpp
	src/ircipher.cpp
	src/irciphpd.cpp
	src/irhash.cpp
	src/irkey.cpp
	src/irkeygen.cpp
	src/irmac.cpp
	src/irpbkdf2.cpp
	src/irsrand.cpp
	src/irtags.cpp
	src/irtypes.cpp
)
	
target_include_directories(irecordcore PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(irecordcore
	PUBLIC ircommon
	PUBLIC Botan2
)
