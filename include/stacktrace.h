/*
** EPITECH PROJECT, 2018
** stacktrace
** File description:
** stack trace creater
*/

#include "structs.h"
#include <stdarg.h>

#ifndef __STACK_H_
#define __STACK_H_

int	delStackTraceEntry(void);
void	printStackTrace(void);
void	initStackTrace(void);
void	addStackTraceEntry(char *fct_name, char *args, ...);
void	freeStackTrace(void);

#endif
