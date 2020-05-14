cmake_minimum_required(VERSION 3.15)
project(linux_programming_study C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
add_library(error utils/error.c)
link_libraries(error)

add_subdirectory(io io)