/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** exceptions.c
*/

#include <stddef.h>
#include "../exceptions.h"
#include "../assert.h"

struct __exceptions_s __exceptionsStack = {
	{
		NULL,
		0,
		0
	},
	NULL
};

const char *get_last_exception_name(void)
{
	if (!__exceptionsStack.last_exception)
		throw(NoActiveException, "No active exception");
	return __exceptionsStack.last_exception->name;
}

const char *get_last_exception_desc(void)
{
	if (!__exceptionsStack.last_exception)
		throw(NoActiveException, "No active exception");
	return __exceptionsStack.last_exception->desc;
}

jmp_buf *__get_last_buffer(void)
{
	unsigned buf = __exceptionsStack.buffers.current_buffer;

	assert(__exceptionsStack.buffers.buffers, "Not init");
	assert(buf, "Too many __endtry calls");
	return &__exceptionsStack.buffers.buffers[buf - 1];
}

const exception_t *get_last_exception(void)
{
	return __exceptionsStack.last_exception;
}

