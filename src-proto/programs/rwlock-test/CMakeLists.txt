cmake_minimum_required(VERSION 3.9)
project(rwlock-test
	VERSION 1.2.3.4)

if (DEFINED MSVC)	
	set(THREAD_LIB "")
else()
	set(THREAD_LIB "pthread")
endif()
	
#-------------------------------------------------------------------------------
# Building the loader
add_executable(rwlock-test
	main.cpp
	IRRWLock.cpp
	IRSemaphore.cpp)
message(STATUS ${THREAD_LIB})
target_link_libraries(rwlock-test
	${THREAD_LIB})


