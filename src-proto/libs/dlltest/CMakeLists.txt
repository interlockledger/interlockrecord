cmake_minimum_required(VERSION 3.9)
project(dlltest)

# Sets the visibility to hidden (GCC and Clang)
if(("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU") OR ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang"))
	message(STATUS "${CMAKE_CXX_COMPILER_ID}: adding flag '-fvisibility=hidden'")
	set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
endif()

#-------------------------------------------------------------------------------
# Building the DLL
# Set files used only by a given platform
if (MSVC)
	set(dlltest_PLATFORM_FILES 
		"dlltest.def"
		"dlltest.rc")
else()
	set(dlltest_PLATFORM_FILES "")
endif()
add_library(dlltest 
	SHARED
	dlltest.cpp
	${dlltest_PLATFORM_FILES})

target_compile_definitions(dlltest
	PUBLIC IR_EXPORTS
)

#-------------------------------------------------------------------------------
# Building the loader
add_executable(dlltestloader
	dlltestloader.cpp
	IRLibrary.cpp)

find_library(DL_LIB "dl")
message(STATUS ${DL_LIB})

target_link_libraries(dlltestloader
	${DL_LIB})



#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

