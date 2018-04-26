cmake_minimum_required(VERSION 3.9)
project(i32obfs-test
	VERSION 1.2.3.4)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_executable(i32obfs-test
	main.cpp
	I32Obfuscator.cpp)

# target_compile_options(i32obfs-test PUBLIC ${OpenMP_CXX_FLAGS})

# target_link_libraries(i32obfs-test gomp)

