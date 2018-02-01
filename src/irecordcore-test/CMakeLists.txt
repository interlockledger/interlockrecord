cmake_minimum_required (VERSION 3.7)
project (irecordcore-test
	VERSION 0.1)

enable_testing()
find_package(GTest REQUIRED)
add_executable(irecordcore-test
	src/tags/IRTagFactoryTest.cpp
	src/tags/IRBaseType16RawTagTest.cpp
	src/tags/IRHashTagTest.cpp
	src/tags/IRPayloadTagTest.cpp
	src/tags/IRSignedTagTest.cpp
	src/tags/IRSigTagTest.cpp
	src/tags/IRTagTypeTest.cpp
	src/tags/IRBlockTagTest.cpp
	src/tags/IRBlockSigTagTest.cpp
	src/tags/IRPubTagTest.cpp
	src/tags/IRHeaderTagTest.cpp
	src/main.cpp)

target_include_directories(irecordcore-test PUBLIC
	$<TARGET_PROPERTY:irecordcore,INTERFACE_INCLUDE_DIRECTORIES>
	"${GTEST_INCLUDE_DIRS}"
)
target_link_libraries(irecordcore-test
	irecord
	irecordcore
	${GTEST_LIBRARIES}
)
add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/irecordcore-test)

