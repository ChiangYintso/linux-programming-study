cmake_minimum_required(VERSION 3.15)
project(progress C)

set(CMAKE_C_STANDARD 11)

add_executable(getpid getpid.c)
add_executable(execl execl.c)
add_executable(fork fork.c)
add_executable(atexit atexit.c)
add_executable(wait wait.c)
add_executable(vfork vfork.c)
add_executable(clone clone.c)