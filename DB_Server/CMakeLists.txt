cmake_minimum_required(VERSION 3.6)
project(DB_Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(DB_Server ${SOURCE_FILES})
target_link_libraries(DB_Server pthread rt)