cmake_minimum_required(VERSION 3.15)
project(signal C)

set(CMAKE_C_STANDARD 11)
LINK_LIBRARIES(pthread)

add_executable(sigint sigint.c)
