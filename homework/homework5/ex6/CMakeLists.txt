cmake_minimum_required(VERSION 3.5)
project(homework5.ex2)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../mod_exp/mod_exp.cpp)
add_executable(homework5.ex6 ${SOURCE_FILES})

target_link_libraries(homework5.ex6 libgmp.so libgmpxx.so)

