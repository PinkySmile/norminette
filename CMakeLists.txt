cmake_minimum_required(VERSION 3.12)
project(norminette C)

set(CMAKE_C_STANDARD 11)

add_executable(
	norminette
	src/main.c
	src/args_management/args.c
	src/args_management/args.h
)

target_link_libraries(
	norminette
        m
)