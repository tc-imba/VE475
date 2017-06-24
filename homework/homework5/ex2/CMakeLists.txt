cmake_minimum_required(VERSION 3.5)
project(homework5.ex2)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../mod_exp/mod_exp.cpp ../ext_euclid/ext_euclid.cpp)
add_executable(homework5.ex2 ${SOURCE_FILES})

