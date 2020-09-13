/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "utils/exceptions.h"
#include "args_management/args.h"

void check_args(int argc, char **argv)
{
	if (argc == 1)
		throw(NoArgumentException, "No argument were provided");
	throw(NotImplementedException, argv[0]);
}

int main(int argc, char **argv)
{
	args_t args;

	init_exceptions();

	try {
		args = parse_args(argc, argv);
	} catch (InvalidArgumentException) {
		fprintf(stderr, "Use %s -h for help.\n", argv[0]);
		return EXIT_FAILURE;
	} catch (InvalidArgumentFormatException) {
		fprintf(stderr, "%s\n", get_last_exception_desc());
		return EXIT_FAILURE;
	}
	end_try;

	free_exceptions();
}