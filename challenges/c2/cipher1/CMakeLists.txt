cmake_minimum_required(VERSION 3.5)
project(c2.cipher1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp aes.c byte.cpp)

add_executable(c2.cipher1 ${SOURCE_FILES})

