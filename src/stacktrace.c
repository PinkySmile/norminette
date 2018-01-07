/*
** EPITECH PROJECT, 2018
** stacktrace
** File description:
** Stack trace management
*/

#include "stacktrace.h"
#include "global3.h"
#include "functions.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void	initStackTrace(void)
{
	stack_trace = malloc(sizeof(*stack_trace));
	stack_trace->data = 0;
	stack_trace->prev = 0;
	stack_trace->next = 0;
	last = stack_trace;
}

void	addStackTraceEntry(char *fct_name, char *args, ...)
{
	char	*buffer1 = 0;
	char	*buffer2 = 0;
	char	*trace = 0;
	va_list	arg_list;

        buffer1 = concat(get_prog_name(), " : ");
	buffer2 = concat(buffer1, fct_name);
	trace = concat(buffer2, "(");
	free(buffer1);
	free(buffer2);
	va_start(arg_list, args);
	for (int i = 0; args[i]; i++) {
		buffer2 = trace;
	        trace = concat(buffer2, va_arg(arg_list, char *));
		free(buffer2);
		switch (args[i]) {
		case 'b':
			buffer2 = trace;
			buffer1 = concat(" = ", va_arg(arg_list, int) ? "TRUE" : "FALSE");
			trace = concat(buffer2, buffer1);
			free(buffer2);
			free(buffer1);
			break;
		case 'd':
			buffer2 = trace;
			buffer1 = concat(" = ", double_to_str(va_arg(arg_list, double)));
			trace = concat(buffer2, buffer1);
			free(buffer2);
			free(buffer1);
			break;
		case 'i':
			buffer2 = trace;
			buffer1 = concat(" = ", int_to_str(va_arg(arg_list, int)));
			trace = concat(buffer2, buffer1);
			free(buffer2);
			free(buffer1);
			break;
		case 'l':
			buffer2 = trace;
			buffer1 = concat(" = ", long_to_str(va_arg(arg_list, long)));
			trace = concat(buffer2, buffer1);
			free(buffer2);
			free(buffer1);
			break;
		case 'p':
			buffer2 = trace;
			buffer1 = concat(" = 0x", my_putnbrbase((long)va_arg(arg_list, void *), "0123456789abcdef"));
			trace = concat(buffer2, buffer1);
			free(buffer2);
			free(buffer1);
		}
		if (i < (int)strlen(args) - 1) {
			buffer1 = trace;
			trace = concat(trace, ", ");
			free(buffer1);
		}
	}
	buffer1 = trace;
	trace = concat(trace, ")");
	free(buffer1);
	va_end(arg_list);
	free(trace);
}

int	delStackTraceEntry(void)
{
	return (0);
}

void	printStackTrace(void)
{
	printf("Stacktrace : \n");
}

void	freeStackTrace(void)
{
	free(stack_trace);
}
