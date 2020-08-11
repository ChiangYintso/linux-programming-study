cmake_minimum_required(VERSION 3.15)
project(generic C)

set(CMAKE_C_STANDARD 11)
add_executable(generic generic.c)
add_executable(time_test time_test.c)