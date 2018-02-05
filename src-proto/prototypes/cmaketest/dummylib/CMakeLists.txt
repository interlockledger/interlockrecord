project (dummylib
	VERSION 0.1)

# Sources
add_library(dummylib STATIC 
	src/dummylib.cpp
)

if(MSVC)
	target_link_libraries(ircommon
		PUBLIC Crypt32.lib
	)
endif()

target_include_directories(dummylib
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	${BOTAN2_INCLUDE_DIR}
)

target_link_libraries(dummylib
	optimized ${BOTAN2_LIB}
	debug ${BOTAN2D_LIB}
)
