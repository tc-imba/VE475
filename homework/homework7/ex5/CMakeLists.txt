cmake_minimum_required(VERSION 3.5)
project(homework7.ex5)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.c)

add_executable(homework7.ex5 ${SOURCE_FILES})
target_link_libraries(homework7.ex5 libgmp.so libgmpxx.so)

