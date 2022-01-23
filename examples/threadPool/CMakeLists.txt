project(threadPool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

cmake_minimum_required(VERSION 2.8) 

set(CMAKE_BUILD_TYPE "Debug")

include_directories(../../include/roughServer/)

aux_source_directory(../../src SRC_DIR)

add_executable(threadPool main.cc ${SRC_DIR}) 
