cmake_minimum_required(VERSION 3.9)
project(botan-test)
include("MSVCCRT.cmake")
include("Botan2.cmake")

add_executable(botan-test
	test.cpp)
	
get_cmake_property(_variableNames VARIABLES)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
	
target_include_directories(botan-test
	 PRIVATE "${BOTAN2_INCLUDE_DIR}")
target_link_libraries(botan-test
	"${BOTAN2_LIB}"
	"${BOTAN2_DEP_LIBS}")
