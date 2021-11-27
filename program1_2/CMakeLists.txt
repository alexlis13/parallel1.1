cmake_minimum_required(VERSION 3.5)

project(program1_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O1")

add_executable(program1_2 main.cpp)
