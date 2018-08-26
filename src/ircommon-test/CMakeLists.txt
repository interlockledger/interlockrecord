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
	src/IRAutoMemoryCleanerTest.h
	src/IRBaseSecureTempTest.h
	src/IRBufferTest.h
	src/IRCodecTest.h
	src/IRDummyRandom.h
	src/IRFloatingPointTest.h
	src/IRHandleListTest.h
	src/IRIDGeneratorTest.h
	src/IRRandomTest.h
	src/IRSecureTempTest.h
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
	src/IRAutoMemoryCleanerTest.cpp
	src/IRBaseSecureTempTest.cpp
	src/IRBufferTest.cpp
	src/IRCodecTest.cpp
	src/IRDummyRandom.cpp
	src/IRFloatingPointTest.cpp
	src/IRHandleListTest.cpp
	src/IRIDGeneratorTest.cpp
	src/IRRandomTest.cpp
	src/IRSecureTempTest.cpp
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

