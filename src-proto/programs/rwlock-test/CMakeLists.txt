cmake_minimum_required(VERSION 3.9)
project(rwlock-test
	VERSION 1.2.3.4)

#-------------------------------------------------------------------------------
# Building the loader
add_executable(rwlock-test
	main.cpp
	IRRWLock.cpp)
target_link_libraries(rwlock-test
	pthread)


