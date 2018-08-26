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
project (irecord-test
	VERSION ${interlockrecord_VERSION})

enable_testing()
add_executable(irecord-tests
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRBlockDisposeTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRBlockLoadTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRBlockParameterTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRBlockSerializeTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRCheckEmergencyClosingTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRCheckParentTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRCheckRootTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRCloseTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRContextCreateTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRContextDisposeTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRDataBlockAddTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRDeinitializeTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IREmergencyCloseTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IREmergencyKeyCreateTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IREmergencyKeyDisposeTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IREmergencyKeyLoadTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IREmergencyKeySerializeTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRGetVersionTest.cpp	
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRInitializeTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRInstanceStateCreateTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRInstanceStateDisposeTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRInstanceStateLoadTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRInstanceStateSerializeTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRInstanceStateSetParamTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRRootBlockCreateTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRRootTemplateCreateTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRRootTemplateDisposeTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRRootTemplateParamTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRRootTemplateParamIntTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRRootTemplateSetEmergencyKeyTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRRootTemplateSetNetworkTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRRootTemplateSetParentTest.cpp
	)

target_link_libraries(irecord-tests
	irecord
	GTest)

add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/irecord-tests)


