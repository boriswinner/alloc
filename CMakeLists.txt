cmake_minimum_required(VERSION 3.10)
project(alloc)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3")
add_executable(alloc main.cpp)