/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** exceptions.h
*/

#ifndef NORMINETTE_EXCEPTIONS_H
#define NORMINETTE_EXCEPTIONS_H


#include <signal.h>
#include <string.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdbool.h>

struct __jmp_buffers_array_s {
	jmp_buf *buffers;
	size_t nb_buffers;
	size_t current_buffer;
};

typedef struct __exception_s {
	const char *name;
	const char *desc;
} exception_t;

struct __exceptions_s {
	struct __jmp_buffers_array_s buffers;
	struct __exception_s *last_exception;
};

extern struct __exceptions_s __exceptionsStack;

void terminate();
const char *get_last_exception_name();
const char *get_last_exception_desc();
const exception_t *get_last_exception();
void __throw(const char *name, const char *desc);
void __rethrow();
jmp_buf *get_last_buffer();

void __init_exceptions();
void __free_exceptions();
void __alloc_exception();
void __alloc_new_buffer();
void __endtry();

#define try if (__alloc_new_buffer(), !setjmp(*get_last_buffer()))
#define catchAll else if (true)
#define catch(exc) else if (strcmp(get_last_exception_name(), #exc) == 0)

#define throw(name, desc) __throw(#name, desc)
#define rethrow __rethrow()

#define init_exceptions() \
if (__exceptionsStack.buffers.buffers)\
	throw("AlreadyInitException", "Exceptions are already init");\
signal(SIGTRAP, SIG_IGN);\
__init_exceptions();\
if (!setjmp(*get_last_buffer())) { do {} while (0)

#define free_exceptions() \
} catchAll { terminate(); } __free_exceptions()\

#define end_try else { rethrow; } __endtry()
#define end_try_return return end_try,

#endif //NORMINETTE_EXCEPTIONS_H
