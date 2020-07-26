cmake_minimum_required(VERSION 3.16)
project(unp_study C)

set(CMAKE_C_STANDARD 11)


add_library(wrap wrap.c)
link_libraries(wrap)

add_library(err_handle err_handle.c)
link_libraries(err_handle)

add_library(writen writen.c)
link_libraries(writen)

add_executable(daytimetcpcli daytimetcpcli.c)
add_executable(daytimetcpcliv6 daytimetcpcliv6.c)
add_executable(daytimetcpsrv daytimetcpsrv.c)
add_executable(tcpserv1 tcpserv1.c)
add_executable(tcpcli1 tcpcli1.c)