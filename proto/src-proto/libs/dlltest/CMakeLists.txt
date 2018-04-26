cmake_minimum_required(VERSION 3.9)
project(dlltest
	VERSION 1.2.3.4)

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
	# Fix the RC file
	string(REGEX REPLACE "\\." "," PROJECT_VERSION_COMMA ${PROJECT_VERSION})
	configure_file(
			"${CMAKE_CURRENT_SOURCE_DIR}/dlltest.rc.in" 
			"${CMAKE_CURRENT_SOURCE_DIR}/dlltest.rc")
		message(STATUS ${PROJECT_VERSION_COMMA})

	set(dlltest_PLATFORM_SRC 
		"${CMAKE_CURRENT_SOURCE_DIR}/dlltest.def"
		"${CMAKE_CURRENT_SOURCE_DIR}/dlltest.rc")
	set(dlltest_PLATFORM_LIBS "")
else()
	set(dlltest_PLATFORM_SRC "")

	find_library(DL_LIB "dl")
	set(dlltest_PLATFORM_LIBS 
			${DL_LIB})
endif()

add_library(dlltest 
	SHARED
	${CMAKE_CURRENT_SOURCE_DIR}/dlltest.cpp
	${dlltest_PLATFORM_SRC})

target_compile_definitions(dlltest
	PUBLIC IR_EXPORTS
)

#-------------------------------------------------------------------------------
# Building the loader
add_executable(dlltestloader
	${CMAKE_CURRENT_SOURCE_DIR}/dlltestloader.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/IRLibrary.cpp
	${dlltest_PLATFORM_SRC})
target_link_libraries(dlltestloader
	${dlltest_PLATFORM_LIBS})

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

