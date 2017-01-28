cmake_minimum_required(VERSION 3.6)
project(Tmp_Client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp lib/SMSystem.h lib/SMSystem.cpp)
add_executable(Tmp_Client ${SOURCE_FILES})
target_link_libraries(Tmp_Client pthread rt boost_serialization)