cmake_minimum_required(VERSION 3.15)
project(progress C)

set(CMAKE_C_STANDARD 11)

LINK_LIBRARIES(pthread)
add_executable(start_thread start_thread.c)
add_executable(mutex mutex.c)
add_executable(semaphore semaphore.c)