/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** terminate.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "../exceptions.h"

void terminate(void)
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
