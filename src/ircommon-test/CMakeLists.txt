cmake_minimum_required (VERSION 3.7)
project (ircommon-test
	VERSION 0.1)

enable_testing()
find_package(GTest REQUIRED)
add_executable(ircommon-test
	src/main.cpp
	src/ILIntTest.cpp
	src/I32FeistelObfuscatorTest.cpp
	src/I32ObfuscatorTest.cpp
	src/IRAlphabetTest.cpp
	src/IRBase2NCodecTest.cpp
	src/IRBase32AlphabetTest.cpp
	src/IRBase64AlphabetTest.cpp
	src/IRBinaryAlphabetTest.cpp
	src/IRBufferTest.cpp
	src/IRCodecTest.cpp
	src/IRGenericAlphabetTest.cpp
	src/IRHexAlphabetTest.cpp
	src/IRJsonArrayTest.cpp
	src/IRJsonBooleanTest.cpp
	src/IRJsonDecimalTest.cpp
	src/IRJsonIntegerTest.cpp
	src/IRJsonNullTest.cpp
	src/IRJsonObjectTest.cpp
	src/IRJsonParserTest.cpp
	src/IRJsonSerializerTest.cpp
	src/IRJsonStringTest.cpp
	src/IRJsonStringTokenizerTest.cpp
	src/IRJsonTokenizerTest.cpp
	src/IRJsonUtilsTest.cpp
	src/IRJsonValueTest.cpp
	src/IRRWLockTest.cpp
	src/IRSemaphoreTest.cpp
	src/IRUtilsTest.cpp)

target_include_directories(ircommon-test 
	PUBLIC 
	$<TARGET_PROPERTY:ircommon,INTERFACE_INCLUDE_DIRECTORIES>
	${GTEST_INCLUDE_DIRS})

target_link_libraries(ircommon-test
	ircommon
	${GTEST_LIBRARIES})

add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ircommon-tests)

