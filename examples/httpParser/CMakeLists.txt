project(httpParser)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

cmake_minimum_required(VERSION 2.8) 

include_directories(../../include/roughServer)

add_executable(httpParser main.cc ../../src/httpParser.cc ../../src/httpResponder.cc) 
