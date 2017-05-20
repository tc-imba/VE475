cmake_minimum_required(VERSION 3.5)
project(homework1)

set(CMAKE_CXX_STANDARD 14)

find_library(libgmp rt /usr/lib)
find_library(libgmpxx rt /usr/lib)

set(SOURCE_FILES main)

add_executable(homework1 ${SOURCE_FILES})
target_link_libraries(homework1 libgmp.so libgmpxx.so)
