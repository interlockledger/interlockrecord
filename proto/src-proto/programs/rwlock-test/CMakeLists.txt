cmake_minimum_required(VERSION 3.9)
project(rwlock-test
	VERSION 1.2.3.4)

find_package(Threads)
if (CMAKE_USE_PTHREADS_INIT)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()
	
#-------------------------------------------------------------------------------
# Building the loader
add_executable(rwlock-test
	main.cpp
	IRRWLock.cpp
	IRSemaphore.cpp)

