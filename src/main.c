/*
** EPITECH PROJECT, 2020
** norminette
** File description:
** main.c
*/

#include <stdio.h>
#include "utils/exceptions.h"
#include "args_management/args.h"
#include "checker/checker.h"
#include "utils/regex.h"
#include "codes.h"

int main(int argc, char **argv)
{
	int code;
	args_t args;

	memset(&args, 0, sizeof(args));
	init_exceptions();

	try {
		args = parse_args(argc, argv);
		code = check_paths(&args, args.paths);
	} catch (InvalidArgumentException) {
		fprintf(stderr, "Use %s -h for help.\n", argv[0]);
		code = RETURN_FAILURE;
	} catch (InvalidArgumentFormatException) {
		fprintf(stderr, "%s\n", get_last_exception_desc());
		code = RETURN_FAILURE;
	} end_try
	free_args(&args);

	free_exceptions();
	return code;
}