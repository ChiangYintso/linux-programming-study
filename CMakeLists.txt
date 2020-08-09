cmake_minimum_required(VERSION 3.16)
project(unp_study C)

set(CMAKE_C_STANDARD 11)


add_library(wrap wrap.c)
link_libraries(wrap)

add_library(err_handle err_handle.c)
link_libraries(err_handle)

add_library(writen writen.c)
link_libraries(writen)

add_library(sig_child_wait tcpcliserv/sig_child_wait.c)
link_libraries(sig_child_wait)

add_executable(daytimetcpcli daytimetcpcli.c)
add_executable(daytimetcpcliv6 daytimetcpcliv6.c)
add_executable(daytimetcpsrv daytimetcpsrv.c)
add_executable(tcpserv1 tcpcliserv/tcpserv1.c)
add_executable(tcpcli1 tcpcliserv/tcpcli1.c)
add_executable(tcpcli_select tcpcliserv/tcpcli_select.c)
add_executable(tcpserv_select tcpcliserv/tcpserv_select.c)
add_executable(tcpserv_poll tcpcliserv/tcpserv_poll.c)