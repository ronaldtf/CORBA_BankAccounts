cmake_minimum_required(VERSION 3.6)
project(CorbaExchange)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Client.cpp)
add_executable(CorbaExchange ${SOURCE_FILES})