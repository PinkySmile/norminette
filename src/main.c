/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** main.c
*/

#include <stdio.h>
#include "utils/exceptions.h"

void check_args(int argc, char **argv)
{
	if (argc == 1)
		throw(NoArgumentException, "No argument were provided");
	throw(NotImplementedException, argv[0]);
}

int main(int argc, char **argv)
{
	init_exceptions();

	try {
		check_args(argc, argv);
	} catch (NotImplementedException) {
		puts("Not implemented yet");
		puts(get_last_exception_desc());
	}
	end_try;

	free_exceptions();
}