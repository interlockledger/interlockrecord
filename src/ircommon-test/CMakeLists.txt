cmake_minimum_required (VERSION 3.7)
project (ircommon-test
	VERSION 0.1)

enable_testing()
find_package(GTest REQUIRED)
add_executable(ircommon-test
	src/codec/IRBase64AlphabetTest.cpp
	src/codec/IRAlphabetTest.cpp
	src/codec/IRHexAlphabetTest.cpp
	src/codec/IRBinaryAlphabetTest.cpp
	src/codec/IRBase32AlphabetTest.cpp
	src/codec/IRBase2NCodecTest.cpp
	src/codec/IRGenericAlphabetTest.cpp
	src/IRBufferTest.cpp
	src/IRCodecTest.cpp
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

