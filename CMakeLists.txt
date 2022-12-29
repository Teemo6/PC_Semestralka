cmake_minimum_required(VERSION 3.10)
project(PC_Semestralka C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -ansi -pedantic")

add_executable(PC_Semestralka main.c config.h hash_table.h hash_table.c hash_table_entry.h hash_table_entry.c error.c error.h classifier.c classifier.h)
target_link_libraries(PC_Semestralka m)
