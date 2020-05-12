cmake_minimum_required(VERSION 3.15)
project(storage C)

set(CMAKE_C_STANDARD 11)

add_library(bar SHARED bar.c)
link_libraries(bar)
add_executable(storage storage.c)
