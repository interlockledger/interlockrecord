cmake_minimum_required (VERSION 3.7)
project (ircommon-test
	VERSION 0.1)

enable_testing()
find_package(GTest REQUIRED)
add_executable(ircommon-test
	src/main.cpp
	src/I32FeistelObfuscatorTest.cpp
	src/I32ObfuscatorTest.cpp
	src/IRAlphabetTest.cpp
	src/IRBase32AlphabetTest.cpp
	src/IRBase64AlphabetTest.cpp
	src/IRBinaryAlphabetTest.cpp
	src/IRGenericAlphabetTest.cpp
	src/IRHexAlphabetTest.cpp
	src/ILIntTest.cpp
	src/IRBufferTest.cpp
	src/IRUtilsTest.cpp)

target_include_directories(ircommon-test PUBLIC
	ircommon
	${GTEST_INCLUDE_DIRS})
target_link_libraries(ircommon-test
	ircommon
	${GTEST_LIBRARIES})

include_directories(${CMAKE_SOURCE_DIR}/ircommon/include)

add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ircommon-tests)

