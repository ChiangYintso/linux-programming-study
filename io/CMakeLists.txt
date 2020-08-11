cmake_minimum_required(VERSION 3.15)
project(io C)

set(CMAKE_C_STANDARD 11)

add_executable(open open.c)
add_executable(nonblocking nonblocking.c)
add_executable(epoll_lt epoll_lt_et.c)