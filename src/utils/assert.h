/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** assert.h
*/

#ifndef NORMINETTE_ASSERT_H
#define NORMINETTE_ASSERT_H

#if !defined(NDEBUG) || defined(_DEBUG)
#include <stdio.h>
#include <stdlib.h>

#define __assert_fmt "Assertion '%s' in function %s at %s:%i failed\n"
#define assert(expr, fmt, ...)\
if (!(expr)) {\
	fprintf(stderr, __assert_fmt, #expr, __FUNCTION__, __FILE__, __LINE__);\
	fprintf(stderr, fmt, ##__VA_ARGS__);\
	abort();\
} else{}
#else
#define assert(expr, ...) (void)(expr)
#endif

#endif //NORMINETTE_ASSERT_H
