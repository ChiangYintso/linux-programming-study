cmake_minimum_required(VERSION 3.15)
project(concurrency C)

set(CMAKE_C_STANDARD 11)
LINK_LIBRARIES(pthread)
add_executable(atomic atomic.c)