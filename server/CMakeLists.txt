cmake_minimum_required(VERSION 3.0)
project(Server)

set(CMAKE_CXX_STANDARD 11)

add_executable(Server main.cpp ../src/functions.cpp ../src/server.cpp ../src/pool.cpp)

target_include_directories(Server PRIVATE ../include)

add_custom_target(CLEAN COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles ${CMAKE_BINARY_DIR}/Makefile ${CMAKE_BINARY_DIR}/CMakeCache.txt)
