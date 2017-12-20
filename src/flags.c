/*
** EPITECH PROJECT, 2017
** flags
** File description:
** flags
*/

#include <stdlib.h>
#include "functions.h"
#include "structs.h"
#include "my.h"
#include <stdio.h>
#include <string.h>

void	display_help(char *prog_name, int fr)
{
	if (fr) {
		printf("USAGE :\n");
		printf("\t%s [-vfunahd] [dossiers/fichiers]\n\n", prog_name);
		printf("DESCRIPTION :\n");
		printf("\t-a :\tActive les options v, u et n (equivaut à -vun)\n\n");
		printf("\t-d :\tFlag de debug à éviter\n\n");
		printf("\t-f :\tChange la langue en français\n\n");
		printf("\t-h :\tAffiche cette page d'aide\n\n");
		printf("\t-n :\tAffiche le nom des fichiers scannés\n\n");
		printf("\t-u :\tCherche les fichiers inutiles dans le repo et\n");
		printf("\t\tles noms invalides\n\n");
		printf("\t-v :\tAffiche la ligne contenant l'erreur et met en\n");
		printf("\t\tvaleur l'erreur\n\n");
		printf("RAPPORTER UN BUG :\n");
		printf("\tSi vous  trouvez un bug, mettez  à jour  le  programme\n");
		printf("\t(Utilisez le script 'update.sh' dans le repo ou encore\n");
		printf("\t<votre alias>-update  si vous  avez utilisé  le script\n");
		printf("\td'installation). Si le bug persiste, lancez 'debug.sh'\n");
		printf("\t(<votre alias>-debug) avec, comme argument, le fichier\n");
		printf("\tayant causé  le bug. Envoyez moi  ensuite  le  fichier\n");
		printf("\tscan.log (vous pouvez aussi  joindre le fichier posant\n");
		printf("\tproblème)   à   l'addresse  \"andgel.halley@epitech.eu\"\n");
		printf("\ten expliquant  le bug rencontrez  et je le  corrigerai\n");
		printf("\tle plus vite possible !\n\n");
		printf("\tNote : Inutile de le lancer en mode debug si  ce n'est\n");
		printf("\tqu'un problème d'affichage (faute de frappe, ...)\n");
		printf("\tLes   scripts   fournis   (update.sh,   debug.sh)   ne\n");
		printf("\tfonctionneront que  si la  norminette se  trouve de le\n");
		printf("\tdossier ~/norminette.  Vous pouvez sinon  les modifier\n");
		printf("\tpour les faire  fonctionner avec votre chemain d'accès\n");
		printf("\tN'hésitez pas à m'envoyer des suggestions par mail !\n");
	} else {
		printf("USAGE :\n");
		printf("\t%s [-vfunahd] [folders/files]\n\n", prog_name);
		printf("DESCRIPTION :\n");
		printf("\t-a :\tEnables v, u and n options (like -vun)\n\n");
		printf("\t-d :\tDebug option (don't use it)\n\n");
		printf("\t-f :\tChange the main language to french\n\n");
		printf("\t-h :\tDisplay this help page\n\n");
		printf("\t-n :\tDisplays the scanned files' names\n\n");
		printf("\t-u :\tFinds unseless files and invalid file names\n\n");
		printf("\t-v :\tDisplays the entire line and where the mistake\n");
		printf("\t\tis in it\n");
		printf("REPORT A BUG :\n");
		printf("\tIf you find a bug, first, update  the program  (Use the\n");
		printf("\t'update.sh'  in  the  repository or, if  you  used  the\n");
		printf("\tinstallation script, <your alias>-update). If it is not\n");
		printf("\tyet patched, run the 'debug.sh' (or <your alias>-debug)\n");
		printf("\twith,  as argument, the  file  which caused  the bug to\n");
		printf("\thappen. Send me, then, the  scan.log file (you can join\n");
		printf("\tthe source  file too) at  \"andgel.halley@epitech.eu\".\n");
		printf("\tExplain briefly in the mail what happened and  I'll fix\n");
		printf("\tas fast as I can !\n\n");
		printf("\tNote : No need to launch  in debug mode if  it's just a\n");
		printf("\tdisplay problem (spelling mistake, ...).\n");
		printf("\tThe given scripts (update.sh, debug.sh) will only work\n");
		printf("\tif the program is stored in ~/norminette. You can also\n");
		printf("\tmodify  the scripts  to make them  work with your  own\n");
		printf("\tpath\n");
		printf("\tYou can also send me ideas by mail !\n");
	}
	exit(0);
}

void	disp_list(list_t *list)
{
	for (; list->next; list = list->next)
		printf("  -  '%s'\n", (char *)list->data);
}

flag	get_flags(int argc, char **args)
{
	flag	flags = {0, 0, 0, 0, 0, 0, 0};
	int	disp = 0;
	char	*dir = 0;

	for (int i = 1; i < argc; i++)
		for (int j = 1; args[i][0] == '-' && args[i][j]; j++)
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
			} else if (args[i][j] == 'I') {
				dir = sub_strings(&args[i][j], 1, strlen(&args[i][j]) + 1, malloc(strlen(&args[i][j]) + 1));
				flags.i_caps = 1;
				load_functions(dir, &flags);
				if (flags.d)
					printf("%i functions are present in the list\n", list_len(flags.fcts));
				if (flags.d) {
					printf("All functions found in directory %s : \n", dir);
					disp_list(flags.fcts);
				}
				free(dir);
				break;
			} else if (args[i][j] == 'd') {
				flags.n = 1;
				flags.d = 1;
			} else if (args[i][j] == 'h')
				disp = 1;
			else {
				printf("%s: Invalid option '%c' (ASCII : %i)\n", args[0], args[i][j], (unsigned char)args[i][j]);
				printf("Use « %s -h » for more informations\n", args[0]);
				free_list(flags.fcts);
				exit(84);
			}
	if (disp)
		display_help(args[0], flags.f);
	return (flags);
}
