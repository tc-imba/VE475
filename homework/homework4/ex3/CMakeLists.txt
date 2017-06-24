cmake_minimum_required(VERSION 3.5)
project(homework4.ex3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ../mod_exp/mod_exp.cpp)
add_executable(homework4.ex3 ${SOURCE_FILES})

