cmake_minimum_required(VERSION 3.7)
project(rrt_explore)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(rrt_explore ${SOURCE_FILES})