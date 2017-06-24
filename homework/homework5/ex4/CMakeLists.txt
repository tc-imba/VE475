cmake_minimum_required(VERSION 3.5)
project(homework5.ex4)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.c rsa.c)

add_executable(homework5.ex4 ${SOURCE_FILES})
target_link_libraries(homework5.ex4 libgmp.so libgmpxx.so)

