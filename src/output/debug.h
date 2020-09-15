/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** debug.h
*/

#ifndef NORMINETTE_DEBUG_H
#define NORMINETTE_DEBUG_H

#ifndef NDEBUG
#define log_debug(format, ...) fprintf(stderr, format"\n", ##__VA_ARGS__)
#else
#define log_debug(...) (void)(0)
#endif

#endif //NORMINETTE_DEBUG_H
