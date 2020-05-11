cmake_minimum_required(VERSION 3.15)
project(linux_network C)

set(CMAKE_C_STANDARD 11)

include_directories ("${PROJECT_SOURCE_DIR}/lib")
add_subdirectory(lib)

add_library(unp lib/unp.h)

add_executable(daytimecpcli daytimecpcli.c)

target_link_libraries(daytimecpcli lib)