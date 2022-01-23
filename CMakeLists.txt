project(roughServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

aux_source_directory(src/ SOURCE_DIR)

cmake_minimum_required(VERSION 2.8) 

include_directories("./include/roughServer")

add_executable(roughServer main.cc ${SOURCE_DIR})
