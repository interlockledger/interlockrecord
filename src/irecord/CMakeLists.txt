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
project (irecord
	VERSION ${interlockrecord_VERSION})
	
# Fix the version strings
configure_file (
	${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in
	${CMAKE_CURRENT_SOURCE_DIR}/src/version.h
)
configure_file (
	${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
	${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
)

if(MSVC)
	set(irecord_DEF_FILE "src/irecord.def")
else()
		set(irecord_DEF_FILE "")
endif()

# Sources
add_library(irecord SHARED
	include/irecord/irecord.h
	include/irecord/irconst.h
	include/irecord/irdll.h
	include/irecord/irerr.h
	src/IRRootTemplateSetParent.cpp
	src/IREmergencyKeyDispose.cpp
	src/IRBlockLoad.cpp
	src/IRInstanceStateSerialize.cpp
	src/IRBlockParameter.cpp
	src/IRInstanceStateCreate.cpp
	src/IRBlockSerialize.cpp
	src/IRClose.cpp
	src/IRContextCreate.cpp
	src/IRCheckParent.cpp
	src/IRRootTemplateParamInt.cpp
	src/IRInstanceStateDispose.cpp
	src/IRBlockDispose.cpp
	src/IREmergencyClose.cpp
	src/IREmergencyKeyLoad.cpp
	src/IRCheckEmergencyClosing.cpp
	src/IRContextDispose.cpp
	src/IRInstanceStateLoad.cpp
	src/IRRootBlockCreate.cpp
	src/IRDeinitialize.cpp
	src/IRGetVersion.cpp
	src/IRRootTemplateParam.cpp
	src/IRRootTemplateDispose.cpp
	src/IRRootTemplateSetEmergencyKey.cpp
	src/IRCheckRoot.cpp
	src/IREmergencyKeyCreate.cpp
	src/version.h
	src/IRInitialize.cpp
	src/IRRootTemplateSetNetwork.cpp
	src/IRInstanceStateSetParam.cpp
	src/IREmergencyKeySerialize.cpp
	src/IRDataBlockAdd.cpp
	src/IRRootTemplateCreate.cpp
	${irecord_DEF_FILE}
)
target_include_directories(irecord PUBLIC 
	include
)
target_compile_definitions(irecord
	PUBLIC IR_EXPORTS
)

