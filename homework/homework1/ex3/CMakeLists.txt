cmake_minimum_required(VERSION 3.5)
project(homework1.ex3)

set(CMAKE_CXX_STANDARD 14)

find_library(libgmp /usr/lib)

set(SOURCE_FILES main)

target_link_libraries(homework1.ex3 libgmp)
add_executable(homework1.ex3 ${SOURCE_FILES})