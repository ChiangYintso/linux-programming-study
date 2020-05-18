cmake_minimum_required(VERSION 3.15)
project(network VERSION 1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)

link_libraries(error)



add_library(tcp_cli tcp_cli.c)
link_libraries(tcp_cli)

add_executable(daytime_tcp_cli daytime_tcp_cli.c)
add_executable(daytime_tcp_srv daytime_tcp_srv.c)