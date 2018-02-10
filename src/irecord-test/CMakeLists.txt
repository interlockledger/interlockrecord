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


