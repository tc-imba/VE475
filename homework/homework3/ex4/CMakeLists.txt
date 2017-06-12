cmake_minimum_required(VERSION 3.5)
project(homework3.ex4)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c aes.c)

add_executable(homework3.ex4 ${SOURCE_FILES})
