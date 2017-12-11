/*
** EPITECH PROJECT, 2017
** flags
** File description:
** flags
*/

#include <stdlib.h>
#include "structs.h"
#include "my.h"

void	display_help(char *prog_name, int fr)
{
	if (fr) {
		my_printf("USAGE :\n");
		my_printf("\t%s [-vfunahd] [dossiers/fichiers]\n\n", prog_name);
		my_printf("DESCRIPTION :\n");
		my_printf("\t-a :\tActive les options v, u et n (equivaut à -vun)\n\n");
		my_printf("\t-d :\tFlag de debug à éviter\n\n");
		my_printf("\t-f :\tChange la langue en français\n\n");
		my_printf("\t-h :\tAffiche cette page d'aide\n\n");
		my_printf("\t-n :\tAffiche le nom des fichiers scannés\n\n");
		my_printf("\t-v :\tAffiche la ligne contenant l'erreur et met en\n");
		my_printf("\t\tvaleur l'erreur\n");
	} else {
		my_printf("USAGE :\n");
		my_printf("\t%s [-vfunahd] [folders/files]\n\n", prog_name);
		my_printf("DESCRIPTION :\n");
		my_printf("\t-a :\tEnables v, u and n options (like -vun)\n\n");
		my_printf("\t-d :\tDebug option (don't use it)\n\n");
		my_printf("\t-f :\tChange the main language to french\n\n");
		my_printf("\t-h :\tDisplay this help page\n\n");
		my_printf("\t-n :\tDisplays the scanned files' names\n\n");
		my_printf("\t-v :\tDisplays the entire line and where the mistake\n");
		my_printf("\t\tis in it\n");
	}
	exit(0);
}

flag	get_flags(int argc, char **args)
{
	flag	flags = {0, 0, 0, 0, 0};
	int	disp = 0;

	for (int i = 1; i < argc; i++)
		for (int j = 0; args[i][0] == '-' && args[i][j]; j++)
			if (args[i][j] == 'v')
				flags.v = 1;
			else if (args[i][j] == 'f')
				flags.f = 1;
			else if (args[i][j] == 'u')
				flags.u = 1;
			else if (args[i][j] == 'n')
				flags.n = 1;
			else if (args[i][j] == 'a') {
				flags.u = 1;
				flags.v = 1;
				flags.n = 1;
			} else if (args[i][j] == 'd') {
				flags.n = 1;
				flags.d = 1;
			} else if (args[i][j] == 'h')
				disp = 1;
	if (disp)
		display_help(args[0], flags.f);
	return (flags);
}
