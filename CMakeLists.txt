cmake_minimum_required(VERSION 3.12)
project(norminette C)

set(CMAKE_C_STANDARD 11)
if ("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
	add_compile_definitions(_DEBUG)
	if (CMAKE_COMPILER_IS_GNUCC)
		add_compile_options(-Wall -Wextra -W -Wshadow -g)
	endif (CMAKE_COMPILER_IS_GNUCC)
else ()
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
	src/output/error_reporting/error_reporting.c
	src/output/error_reporting.h
	src/output/color.c
	src/output/color.h
	src/utils/exceptions/exceptions.c
	src/utils/exceptions.h
	src/utils/alloc.c
	src/utils/alloc.h
	src/args_management/update.c
	src/args_management/update.h
	src/args_management/help.c
	src/args_management/help.h
	src/utils/exceptions/throw.c
	src/utils/exceptions/alloc.c
	src/utils/exceptions/terminate.c
	src/utils/assert.h
	src/checker/checker.c
	src/checker/checker.h
	src/utils/concat.c
	src/utils/concat.h
	src/utils/files/file_types.c
	src/checker/is_file_useless.c
	src/checker/is_file_useless.h
	src/output/error_reporting/display_error_start.c
	src/utils/regex.c
	src/utils/regex.h
	src/utils/files.h
	src/utils/files/get_file_length.c
	src/checker/convert_state.c src/checker/convert_state.h src/output/error_reporting/display_style_error.c src/output/error_reporting/display_style_error.h src/args_management/handlers.c src/args_management/handlers.h src/utils/is_in_list.c src/utils/is_in_list.h)

target_link_libraries(
	norminette
        m
)