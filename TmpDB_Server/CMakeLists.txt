cmake_minimum_required(VERSION 3.6)
project(TmpDB_Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(TmpDB_Server ${SOURCE_FILES})