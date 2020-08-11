cmake_minimum_required(VERSION 3.15)
project(linux_programming_study C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
add_library(error common/error.c)
link_libraries(error)

add_library(wrap common/wrap.c)
link_libraries(wrap)

add_subdirectory(io io)
add_subdirectory(network network)