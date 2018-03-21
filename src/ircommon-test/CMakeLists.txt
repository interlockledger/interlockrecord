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
	src/codec/IRAlphabetTest.h
	src/codec/IRBase2NCodecTest.h
	src/codec/IRBase32AlphabetTest.h
	src/codec/IRBase64AlphabetTest.h
	src/codec/IRBinaryAlphabetTest.h
	src/codec/IRGenericAlphabetTest.h
	src/codec/IRHexAlphabetTest.h
	src/crypto/I32FeistelObfuscatorTest.h
	src/crypto/I32ObfuscatorTest.h
	src/crypto/IRARC4RandomTest.h
	src/crypto/IRARC4Test.h
	src/crypto/IRProtectedMemoryTest.h
	src/ILIntTest.h
	src/iltags/ILBaseTagArrayTagTest.h
	src/iltags/ILBaseTagListTagTest.h
	src/iltags/ILBasicFixedOpaqueTagTest.h
	src/iltags/ILBasicFloatTagTest.h
	src/iltags/ILBasicIntTagTest.h
	src/iltags/ILBigDecimalTagTest.h
	src/iltags/ILBigIntTagTest.h
	src/iltags/ILBinary128TagTest.h
	src/iltags/ILBinary32TagTest.h
	src/iltags/ILBinary64TagTest.h
	src/iltags/ILBoolTagTest.h
	src/iltags/ILByteArrayTagTest.h
	src/iltags/ILILIntArrayTagTest.h
	src/iltags/ILILIntTagTest.h
	src/iltags/ILInt16TagTest.h
	src/iltags/ILInt32TagTest.h
	src/iltags/ILInt64TagTest.h
	src/iltags/ILInt8TagTest.h
	src/iltags/ILNullTagTest.h
	src/iltags/ILRawTagTest.h
	src/iltags/ILStandardTagFactoryTest.h
	src/iltags/ILStringTagTest.h
	src/iltags/ILTagArrayTagTest.h
	src/iltags/ILTagFactoryTest.h
	src/iltags/ILTagSeqTagTest.h
	src/iltags/ILTagTest.h
	src/iltags/ILTagUtilTest.h
	src/iltags/ILUInt16TagTest.h
	src/iltags/ILUInt32TagTest.h
	src/iltags/ILUInt64TagTest.h
	src/iltags/ILUInt8TagTest.h
	src/IRBufferTest.h
	src/IRCodecTest.h
	src/IRDummyRandom.h
	src/IRFloatingPointTest.h
	src/IRHandleListTest.h
	src/IRIDGeneratorTest.h
	src/IRRandomTest.h
	src/IRSharedPtrHandleListTest.h
	src/IRUtilsTest.h
	src/IRXORShifRandomTest.h
	src/json/IRJsonArrayTest.h
	src/json/IRJsonBooleanTest.h
	src/json/IRJsonDecimalTest.h
	src/json/IRJsonIntegerTest.h
	src/json/IRJsonNullTest.h
	src/json/IRJsonObjectTest.h
	src/json/IRJsonParserTest.h
	src/json/IRJsonSerializerTest.h
	src/json/IRJsonStringTest.h
	src/json/IRJsonStringTokenizerTest.h
	src/json/IRJsonTokenizerTest.h
	src/json/IRJsonUtilsTest.h
	src/json/IRJsonValueTest.h
	src/threading/IRRWLockTest.h
	src/threading/IRSemaphoreTest.h
	src/threading/IRSharedRandomTest.h
	src/codec/IRAlphabetTest.cpp
	src/codec/IRBase2NCodecTest.cpp
	src/codec/IRBase32AlphabetTest.cpp
	src/codec/IRBase64AlphabetTest.cpp
	src/codec/IRBinaryAlphabetTest.cpp
	src/codec/IRGenericAlphabetTest.cpp
	src/codec/IRHexAlphabetTest.cpp
	src/crypto/I32FeistelObfuscatorTest.cpp
	src/crypto/I32ObfuscatorTest.cpp
	src/crypto/IRARC4RandomTest.cpp
	src/crypto/IRARC4Test.cpp
	src/crypto/IRProtectedMemoryTest.cpp
	src/ILIntTest.cpp
	src/iltags/ILBaseTagArrayTagTest.cpp
	src/iltags/ILBaseTagListTagTest.cpp
	src/iltags/ILBasicFixedOpaqueTagTest.cpp
	src/iltags/ILBasicFloatTagTest.cpp
	src/iltags/ILBasicIntTagTest.cpp
	src/iltags/ILBigDecimalTagTest.cpp
	src/iltags/ILBigIntTagTest.cpp
	src/iltags/ILBinary128TagTest.cpp
	src/iltags/ILBinary32TagTest.cpp
	src/iltags/ILBinary64TagTest.cpp
	src/iltags/ILBoolTagTest.cpp
	src/iltags/ILByteArrayTagTest.cpp
	src/iltags/ILILIntArrayTagTest.cpp
	src/iltags/ILILIntTagTest.cpp
	src/iltags/ILInt16TagTest.cpp
	src/iltags/ILInt32TagTest.cpp
	src/iltags/ILInt64TagTest.cpp
	src/iltags/ILInt8TagTest.cpp
	src/iltags/ILNullTagTest.cpp
	src/iltags/ILRawTagTest.cpp
	src/iltags/ILStandardTagFactoryTest.cpp
	src/iltags/ILStringTagTest.cpp
	src/iltags/ILTagArrayTagTest.cpp
	src/iltags/ILTagFactoryTest.cpp
	src/iltags/ILTagSeqTagTest.cpp
	src/iltags/ILTagTest.cpp
	src/iltags/ILTagUtilTest.cpp
	src/iltags/ILUInt16TagTest.cpp
	src/iltags/ILUInt32TagTest.cpp
	src/iltags/ILUInt64TagTest.cpp
	src/iltags/ILUInt8TagTest.cpp
	src/IRBufferTest.cpp
	src/IRCodecTest.cpp
	src/IRDummyRandom.cpp
	src/IRFloatingPointTest.cpp
	src/IRHandleListTest.cpp
	src/IRIDGeneratorTest.cpp
	src/IRRandomTest.cpp
	src/IRSharedPtrHandleListTest.cpp
	src/IRUtilsTest.cpp
	src/IRXORShifRandomTest.cpp
	src/json/IRJsonArrayTest.cpp
	src/json/IRJsonBooleanTest.cpp
	src/json/IRJsonDecimalTest.cpp
	src/json/IRJsonIntegerTest.cpp
	src/json/IRJsonNullTest.cpp
	src/json/IRJsonObjectTest.cpp
	src/json/IRJsonParserTest.cpp
	src/json/IRJsonSerializerTest.cpp
	src/json/IRJsonStringTest.cpp
	src/json/IRJsonStringTokenizerTest.cpp
	src/json/IRJsonTokenizerTest.cpp
	src/json/IRJsonUtilsTest.cpp
	src/json/IRJsonValueTest.cpp
	src/main.cpp
	src/threading/IRRWLockTest.cpp
	src/threading/IRSemaphoreTest.cpp
	src/threading/IRSharedRandomTest.cpp
)

target_link_libraries(ircommon-test
	ircommon
	GTest)

add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ircommon-tests)

