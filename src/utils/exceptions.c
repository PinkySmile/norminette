/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** exceptions.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "exceptions.h"

struct __exceptions_s __exceptionsStack = {
	{
		NULL,
		0,
		0
	},
	NULL
};

void terminate()
{
	struct __exception_s *_exc = __exceptionsStack.last_exception;

	fprintf(stderr, "terminate called ");
	if (_exc) {
		fprintf(stderr, "after throwing a '%s':\n", _exc->name);
		fprintf(stderr, "  Description: %s\n", _exc->desc);
	} else
		fprintf(stderr, "without an active exception.\n");
	abort();
}

const char *get_last_exception_name()
{
	if (!__exceptionsStack.last_exception)
		throw (NoActiveException, "No active exception");
	return __exceptionsStack.last_exception->name;
}

const char *get_last_exception_desc()
{
	if (!__exceptionsStack.last_exception)
		throw (NoActiveException, "No active exception");
	return __exceptionsStack.last_exception->desc;
}

const exception_t *get_last_exception()
{
	return __exceptionsStack.last_exception;
}

void __alloc_exception()
{
	if (!__exceptionsStack.last_exception)
		__exceptionsStack.last_exception =\
		malloc(sizeof(*__exceptionsStack.last_exception));
}

void __throw(const char *name, const char *desc)
{
	__alloc_exception();
	__exceptionsStack.last_exception->name = name;
	__exceptionsStack.last_exception->desc = desc;
	__rethrow();
}

void __rethrow()
{
	unsigned buf = --__exceptionsStack.buffers.current_buffer;

	raise(SIGTRAP);
	longjmp(__exceptionsStack.buffers.buffers[buf], true);
}

jmp_buf *get_last_buffer()
{
	unsigned buf = __exceptionsStack.buffers.current_buffer;

	return &__exceptionsStack.buffers.buffers[buf - 1];
}

void __init_exceptions()
{
	if (!__exceptionsStack.buffers.nb_buffers)
		__alloc_new_buffer();
	__exceptionsStack.buffers.current_buffer = 1;
}

void __free_exceptions()
{
	free(__exceptionsStack.last_exception);
	__exceptionsStack.last_exception = NULL;

	free(__exceptionsStack.buffers.buffers);
	__exceptionsStack.buffers.nb_buffers = 0;
	__exceptionsStack.buffers.buffers = NULL;
}

void __alloc_new_buffer()
{
	unsigned current = __exceptionsStack.buffers.current_buffer;
	unsigned size = __exceptionsStack.buffers.nb_buffers;
	jmp_buf *ptr = __exceptionsStack.buffers.buffers;

	if (size <= current) {
		__exceptionsStack.buffers.nb_buffers++;
		ptr = realloc(
			__exceptionsStack.buffers.buffers,
			__exceptionsStack.buffers.nb_buffers * sizeof(*ptr)
		);
		if (!ptr)
			__throw("bad_alloc", "Cannot grow exception stack");
	}
	__exceptionsStack.buffers.current_buffer++;
	__exceptionsStack.buffers.buffers = ptr;
}

void __endtry()
{
	__exceptionsStack.buffers.current_buffer--;
	free(__exceptionsStack.last_exception);
	__exceptionsStack.last_exception = NULL;
}

