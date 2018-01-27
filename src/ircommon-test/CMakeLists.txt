cmake_minimum_required (VERSION 3.7)
project (ircommon-test
	VERSION 0.1)

enable_testing()
find_package(GTest REQUIRED)
add_executable(ircommon-test
	src/iltags/ILStringTagTest.cpp
	src/iltags/ILInt8TagTest.cpp
	src/iltags/ILInt16TagTest.cpp
	src/iltags/ILTagListTagTest.cpp
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
	src/codec/IRBase64AlphabetTest.cpp
	src/codec/IRAlphabetTest.cpp
	src/codec/IRHexAlphabetTest.cpp
	src/codec/IRBinaryAlphabetTest.cpp
	src/codec/IRBase32AlphabetTest.cpp
	src/codec/IRBase2NCodecTest.cpp
	src/codec/IRGenericAlphabetTest.cpp
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
	src/crypto/I32FeistelObfuscatorTest.cpp
	src/crypto/I32ObfuscatorTest.cpp
	src/ILIntTest.cpp
	src/IRHandleListTest.cpp
	src/main.cpp)

target_include_directories(ircommon-test 
	PUBLIC 
	$<TARGET_PROPERTY:ircommon,INTERFACE_INCLUDE_DIRECTORIES>
	${GTEST_INCLUDE_DIRS})

target_link_libraries(ircommon-test
	ircommon
	${GTEST_LIBRARIES})

add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ircommon-tests)

