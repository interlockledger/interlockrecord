project (dummylib
	VERSION 0.1)

# Sources
add_library(dummylib STATIC 
	src/dummylib.cpp
)

target_link_libraries(dummylib
	PUBLIC Botan2)

target_include_directories(dummylib
	PUBLIC Botan2
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include	
)
