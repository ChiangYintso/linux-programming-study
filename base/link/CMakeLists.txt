cmake_minimum_required(VERSION 3.15)
project(link C)

set(CMAKE_C_STANDARD 11)

add_library(fun1 fun1.c)
link_libraries(fun1)

add_executable(main main.c)