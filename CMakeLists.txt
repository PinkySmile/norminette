cmake_minimum_required(VERSION 3.12)
project(norminette C)

set(CMAKE_C_STANDARD 11)
if ("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
	add_compile_definitions(_DEBUG)
	if (CMAKE_COMPILER_IS_GNUCC)
		add_compile_options(-Wall -Wextra -W -Wshadow -g)
	endif (CMAKE_COMPILER_IS_GNUCC)
endif ()

if ("${CMAKE_BUILD_TYPE}" STREQUAL Release)
	add_compile_definitions(NDEBUG)
endif ()

add_executable(
	norminette
	src/main.c
	src/args_management/args.c
	src/args_management/args.h
	src/data/style_errors.c
	src/data/style_errors.h
	src/output/debug.c
	src/output/debug.h
	src/output/error_reporting.c
	src/output/error_reporting.h
	src/output/color.c
	src/output/color.h
)

target_link_libraries(
	norminette
        m
)