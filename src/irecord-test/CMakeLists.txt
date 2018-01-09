cmake_minimum_required (VERSION 3.7)
project (irecord-test
	VERSION 0.1)

enable_testing()
find_package(Threads)
find_package(GTest REQUIRED)
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
	${CMAKE_CURRENT_SOURCE_DIR}/src/IREmergencyKeySerializedTest.cpp
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
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRRootTemplateSetEmergencyKeyTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRRootTemplateSetNetworkTest.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/IRRootTemplateSetParentTest.cpp
	)
target_include_directories(irecord-tests PUBLIC
	irecord
	"${GTEST_INCLUDE_DIRS}"
)
target_link_libraries(
	irecord-tests
	irecord
	${GTEST_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT})

add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/irecord-tests)


