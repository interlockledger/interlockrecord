cmake_minimum_required(VERSION 3.9)
project (irecord
	VERSION 0.1.0.0)
	
# Fix the version strings
configure_file (
	${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in
	${CMAKE_CURRENT_SOURCE_DIR}/src/version.h
)
configure_file (
	${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
	${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
)

if(MSVC)
	set(irecord_DEF_FILE "src/irecord.def")
else()
		set(irecord_DEF_FILE "")
endif()

# Sources
add_library(irecord SHARED
	src/IRBlockDispose.cpp
	src/IRBlockLoad.cpp
	src/IRBlockParameter.cpp
	src/IRBlockSerialize.cpp
	src/IRCheckEmergencyClosing.cpp
	src/IRCheckParent.cpp
	src/IRCheckRoot.cpp
	src/IRClose.cpp
	src/IRContextCreate.cpp
	src/IRContextDispose.cpp
	src/IRDataBlockAdd.cpp
	src/IRDeinitialize.cpp
	src/IREmergencyClose.cpp
	src/IREmergencyKeyCreate.cpp
	src/IREmergencyKeyDispose.cpp
	src/IREmergencyKeyLoad.cpp
	src/IREmergencyKeySerialized.cpp
	src/IRGetVersion.cpp
	src/IRInitialize.cpp
	src/IRInstanceStateCreate.cpp
	src/IRInstanceStateDispose.cpp
	src/IRInstanceStateLoad.cpp
	src/IRInstanceStateSerialize.cpp
	src/IRInstanceStateSetParam.cpp
	src/IRRootBlockCreate.cpp
	src/IRRootTemplateCreate.cpp
	src/IRRootTemplateDispose.cpp
	src/IRRootTemplateParam.cpp
	src/IRRootTemplateSetEmergencyKey.cpp
	src/IRRootTemplateSetNetwork.cpp
	src/IRRootTemplateSetParent.cpp
	${irecord_DEF_FILE}
)
target_include_directories(irecord PUBLIC 
	include
)
target_compile_definitions(irecord
	PUBLIC IR_EXPORTS
)

