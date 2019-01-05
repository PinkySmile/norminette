cmake_minimum_required(VERSION 3.12)
project(norminette C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(norminette
        include/functions.h
        include/global.h
        include/global2.h
        include/global3.h
        include/macros.h
        include/my.h
        include/stacktrace.h
        include/structs.h
        src/catch_sig.c
        src/compare_strings.c
        src/concat.c
        src/display_cappuccino.c
        src/double_to_str.c
        src/flags.c
        src/free_list.c
        src/get_env_vars.c
        src/get_nbrlen.c
        src/int_to_str.c
        src/load_functions.c
        src/long_to_str.c
        src/main.c
        src/my_malloc.c
        src/my_putnbr_base.c
        src/my_showstr.c
        src/scan.c
        src/scan_file.c
        src/stacktrace.c
        src/sub_strings.c)

target_link_libraries(norminette
        m)