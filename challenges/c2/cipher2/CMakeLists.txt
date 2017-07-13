cmake_minimum_required(VERSION 3.5)
project(c2.cipher2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp rc5.cpp byte.cpp)

add_executable(c2.cipher2 ${SOURCE_FILES})

