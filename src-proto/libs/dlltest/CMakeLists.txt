cmake_minimum_required(VERSION 3.9)
project(dlltest)

# Set flags
if (MSVC)
	set(dlltest_DEF_FILE "main.def")
endif()
if(("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU") OR ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang"))
	message(STATUS "${CMAKE_CXX_COMPILER_ID}: adding flag '-fvisibility=hidden'")
	set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
endif()

add_library(dlltest 
	SHARED
	main.cpp
	${dlltest_DEF_FILE})

target_compile_definitions(dlltest
	PUBLIC IR_EXPORTS
) 

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()




