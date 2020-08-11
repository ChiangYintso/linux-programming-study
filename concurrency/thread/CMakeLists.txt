cmake_minimum_required(VERSION 3.15)
project(thread VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

add_definitions(-D DEBUG)

LINK_LIBRARIES(pthread)

include_directories("${PROJECT_SOURCE_DIR}/lib")

add_library(block_queue lib/block_queue.c)
link_libraries(block_queue)

add_executable(start_thread start_thread.c)
add_executable(mutex mutex.c)
add_executable(semaphore semaphore.c)


add_executable(producer_consumer producer_consumer.c)
