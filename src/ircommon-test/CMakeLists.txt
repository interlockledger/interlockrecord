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
project (ircommon-test
	VERSION ${interlockrecord_VERSION})

enable_testing()
add_executable(ircommon-test
	src/iltags/ILStringTagTest.cpp
	src/iltags/ILInt8TagTest.cpp
	src/iltags/ILInt16TagTest.cpp
	src/iltags/ILTagListTagTest.cpp
	src/iltags/ILBasicFloatTagTest.cpp
	src/iltags/ILBasicIntTagTest.cpp
	src/iltags/ILInt64TagTest.cpp
	src/iltags/ILStandardTagFactoryTest.cpp
	src/iltags/ILBinary32TagTest.cpp
	src/iltags/ILUInt8TagTest.cpp
	src/iltags/ILTagFactoryTest.cpp
	src/iltags/ILTagTest.cpp
	src/iltags/ILBinary128TagTest.cpp
	src/iltags/ILBigDecimalTagTest.cpp
	src/iltags/ILByteArrayTagTest.cpp
	src/iltags/ILILIntArrayTagTest.cpp
	src/iltags/ILBinary64TagTest.cpp
	src/iltags/ILBigIntTagTest.cpp
	src/iltags/ILUInt64TagTest.cpp
	src/iltags/ILRawTagTest.cpp
	src/iltags/ILUInt32TagTest.cpp
	src/iltags/ILUInt16TagTest.cpp
	src/iltags/ILBoolTagTest.cpp
	src/iltags/ILNullTagTest.cpp
	src/iltags/ILTagArrayTagTest.cpp
	src/iltags/ILBasicFixedOpaqueTagTest.cpp
	src/iltags/ILInt32TagTest.cpp
	src/iltags/ILILIntTagTest.cpp
	src/iltags/ILTagUtilTest.cpp
	src/codec/IRBase64AlphabetTest.cpp
	src/codec/IRAlphabetTest.cpp
	src/codec/IRHexAlphabetTest.cpp
	src/codec/IRBinaryAlphabetTest.cpp
	src/codec/IRBase32AlphabetTest.cpp
	src/codec/IRBase2NCodecTest.cpp
	src/codec/IRGenericAlphabetTest.cpp
	src/crypto/I32FeistelObfuscatorTest.cpp
	src/crypto/I32ObfuscatorTest.cpp
	src/crypto/IRARC4Test.cpp
	src/crypto/IRProtectedMemoryTest.cpp
	src/IRBufferTest.cpp
	src/IRCodecTest.cpp
	src/IRFloatingPointTest.cpp
	src/IRIDGeneratorTest.cpp
	src/IRSharedPtrHandleListTest.cpp
	src/IRUtilsTest.cpp
	src/json/IRJsonSerializerTest.cpp
	src/json/IRJsonValueTest.cpp
	src/json/IRJsonUtilsTest.cpp
	src/json/IRJsonNullTest.cpp
	src/json/IRJsonTokenizerTest.cpp
	src/json/IRJsonObjectTest.cpp
	src/json/IRJsonBooleanTest.cpp
	src/json/IRJsonArrayTest.cpp
	src/json/IRJsonStringTest.cpp
	src/json/IRJsonStringTokenizerTest.cpp
	src/json/IRJsonDecimalTest.cpp
	src/json/IRJsonParserTest.cpp
	src/json/IRJsonIntegerTest.cpp
	src/threading/IRRWLockTest.cpp
	src/threading/IRSemaphoreTest.cpp
	src/ILIntTest.cpp
	src/IRHandleListTest.cpp
	src/main.cpp)

target_link_libraries(ircommon-test
	ircommon
	GTest)

add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ircommon-tests)

