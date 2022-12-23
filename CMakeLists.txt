cmake_minimum_required(VERSION 3.23)
project(PC_Semestralka C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -ansi -pedantic")

add_executable(PC_Semestralka main.c config.h hash_table.h hash_table.c)
