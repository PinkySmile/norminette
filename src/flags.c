/*
** EPITECH PROJECT, 2017
** flags
** File description:
** flags
*/

#include <stdlib.h>
#include "stacktrace.h"
#include "functions.h"
#include "structs.h"
#include "my.h"
#include <stdio.h>
#include <string.h>

void	disp_en_help(char *prog_name)
{
	printf("USAGE :\n");
	printf("\t%s [-vcfunahd] [-I<path>] [folders/files]\n\n", prog_name);
	printf("DESCRIPTION :\n");
	printf("\t-a :\t\tEnables v, u, b, I. and l options (like -vbunlI.)\n\n");
	printf("\t-b :\t\tDisplays all banned functions found (useless without -I)\n\n");
	printf("\t-c :\t\tDisables colors\n\n");
	printf("\t-d :\t\tDebug option (don't use it)\n\n");
	printf("\t-f :\t\tChange the main language to french\n\n");
	printf("\t-l :\t\tAutomaticaly answer yes for large files (> 1 Mo)\n\n");
	printf("\t-h :\t\tDisplay this help page\n\n");
	printf("\t-n :\t\tDisplays the scanned files' names\n\n");
	printf("\t-t :\t\tEnables the stacktrace\n\n");
	printf("\t-s :\t\tAutomaticaly answer no for large files (> 1 Mo)\n");
	printf("\t\t\tOverrides -l\n\n");
	printf("\t-u :\t\tFinds useless files and invalid file names\n\n");
	printf("\t-v :\t\tDisplays the entire line and where the mistake\n");
	printf("\t\t\tis in it\n\n");
	printf("\t-I<path> : \tUsing the I flag enables the forbidden functions\n");
	printf("\t\t\tchecking in .c files. Using this flag transform the remaining\n");
	printf("\t\t\tstring into the path of the folder or file which contains\n");
	printf("\t\t\tallowed functions. The program will save every function\n");
	printf("\t\t\tdeclared in those files/folders (only .c and .h files)\n");
	printf("\t\t\tand use them as only allowed functions. That means that all\n");
	printf("\t\t\tfunctions which are not declared in these files will be\n");
	printf("\t\t\tthe forbidden functions. All the allowed system calls have\n");
	printf("\t\t\thave to be declared in a .h or .c file. No need to declare\n");
	printf("\t\t\tthe functions properly. You juste have to follow this exemple\n");
	printf("\t\t\t\t\tvoid function();\n");
	printf("\t\t\tNote : severals -I can be used at the same if you have many include\n");
	printf("\t\t\tand source folders with, for exemple, the CSFML\n");
	printf("\t\t\tCSMFL's includes are in the folder /usr/local/include/SFML.\n");
	printf("\t\t\tFor graphical projects use -I/usr/local/include/SFML .\n\n");
	printf("EXEMPLES :\n");
	printf("\t%s :\n\t\tLaunch a basic test on the current folder\n\n", prog_name);
	printf("\t%s src test.c :\n\t\tLaunch a basic test in the folder 'src' and on the file 'test.c'\n\n", prog_name);
	printf("\t%s -vfIinclude -I/usr -I../sys.h\n\t\tLaunch the program in verbose mode, in french\n", prog_name);
	printf("\t\twith forbidden function wich are not found neither in the folders 'include' and '/usr' nor in the file '../sys.h'\n\n");
	printf("RETURN VALUES :\n");
	printf("\tIf no mistakes are found, the program exit with code 0.\n");
	printf("\tIf one or many mistakes are found, the program exit with code 1.\n\n");
	printf("REPORT A BUG :\n");
	printf("\tIf you find a bug, first, update  the program  (Use the\n");
	printf("\t'update.sh'  in  the  repository or, if  you  used  the\n");
	printf("\tinstallation script, <your alias>-update). If it is not\n");
	printf("\tyet patched, run the 'debug.sh' (or <your alias>-debug)\n");
	printf("\twith,  as argument, the  file  which caused  the bug to\n");
	printf("\thappen. Send me, then, the  scan.log file (you can join\n");
	printf("\tthe source  file too) at  \"andgel.halley@epitech.eu\".\n");
	printf("\tExplain briefly in the mail what happened and  I'll fix\n");
	printf("\tas fast as I can !\n\tYou  can also send it on discord or\n");
	printf("\topen a new issue ticket on github.\n\n");
	printf("\tNote : No need to launch  in debug mode if  it's just a\n");
	printf("\tdisplay problem (spelling mistake, ...).\n");
	printf("\tThe given scripts (update.sh, debug.sh) will only work\n");
	printf("\tif the program is stored in ~/norminette. You can also\n");
	printf("\tmodify  the scripts  to make them  work with your  own\n");
	printf("\tpath\n");
	printf("\tYou can also send me ideas by mail !\n");
	printf("UPDATES :\n");
	printf("\tif you want to get notified on new updates, you can join\n");
	printf("\tthis server https://discord.gg/RgDbJDW\n");
}

void	disp_fr_help(char *prog_name)
{
	printf("USAGE :\n");
	printf("\t%s [-vcfunahd] [-I<chemin>] [dossiers/fichiers]\n\n", prog_name);
	printf("DESCRIPTION :\n");
	printf("\t-a :\t\tActive les options v, u, b, I. et l (equivaut à -vbulI.)\n\n");
	printf("\t-b :\t\tAffiche une liste des fonctions interdites trouvées (inutile sans -I)\n\n");
	printf("\t-c :\t\tDésactive les couleurs\n\n");
	printf("\t-d :\t\tFlag de debug à éviter\n\n");
	printf("\t-f :\t\tChange la langue en français\n\n");
	printf("\t-h :\t\tAffiche cette page d'aide\n\n");
	printf("\t-l :\t\tScan les fichiers de grande taille sans demander (> 1 Mo)\n\n");
	printf("\t-n :\t\tAffiche le nom des fichiers scannés\n\n");
	printf("\t-t :\t\tActive le stacktrace\n\n");
	printf("\t-s :\t\tNe scan pas les fichiers de grande taille (> 1 Mo)\n");
	printf("\t\t\tOutrepasse -l\n\n");
	printf("\t-u :\t\tCherche les fichiers inutiles dans le repo et\n");
	printf("\t\t\tles noms invalides\n\n");
	printf("\t-v :\t\tAffiche la ligne contenant l'erreur et met en\n");
	printf("\t\t\tvaleur l'erreur\n\n");
	printf("\t-I<chemin> : \tUtiliser le flag I permet d'activer la détection des\n");
	printf("\t\t\tfonctions dans les dossiers et fichiers .c. Utiliser\n");
	printf("\t\t\tce flag transforme tous les charactères suivants en\n");
	printf("\t\t\ten un chemin d'accès vers un dossier ou fichier. La\n");
	printf("\t\t\tnorminette va sauvegarder toutes les fonctions déclarées\n");
	printf("\t\t\tdans les fichier .c et .h et les interprèter comme fonctions\n");
	printf("\t\t\tautorisées. Toute fonction n'étant pas déclaré ici seront\n");
	printf("\t\t\tdonc considéré comme des fonction interdites. Les fonctions\n");
	printf("\t\t\tsystèmes autorisées doivent avoir une définition dans un\n");
	printf("\t\t\tfichier .h ou .c. La définition des fonctions n'as pas a être\n");
	printf("\t\t\tcomplète ! Vous pouvez toutes les déclarer comme ceci\n");
	printf("\t\t\t\t\tvoid fonction();\n");
	printf("\t\t\tÀ noter aussi que plusieurs -I peuvent être utiliser en même\n");
	printf("\t\t\ttemps si vous avez plusieurs dossiers d'include comme avec\n");
	printf("\t\t\tla CSMFL par exemple. Les includes de la CSML sont stocké dans le\n");
	printf("\t\t\tdossier /usr/local/include/SFML.\n");
	printf("\t\t\tUtiliser donc -I/usr/local/include/SFML pour vos projets graphiques.\n\n");
	printf("EXEMPLES :\n");
	printf("\t%s :\n\t\tLance un scan basique dans le dossier courant\n\n", prog_name);
	printf("\t%s src test.c :\n\t\tLance un scan basique dans le dossier 'src' et sur le fichier 'test.c'\n\n", prog_name);
	printf("\t%s -vfIinclude -I/usr -I../sys.h\n\t\tLance un scan en mode verbeux en français avec la détections des fonctions interdites\n", prog_name);
	printf("\t\tavec les fonctions autorisées dans les dossiers 'include' et '/usr' et dans le fichier '../sys.h'\n\n");
	printf("VALEURS DE RETOUR :\n");
	printf("\tSi aucune erreur n'est trouvée, le programme sort avec le code 0.\n");
	printf("\tSi une ou plusieurs erreurs ont été détectées, le programme sort avec le code 1.\n\n");
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
	printf("\tle plus vite possible !\n\tVous pouvez aussi m'envoyer un");
	printf("message sur\n\tdiscord ou ouvrir un ticket github.\n\n");
	printf("\tNote : Inutile de le lancer en mode debug si  ce n'est\n");
	printf("\tqu'un problème d'affichage (faute de frappe, ...)\n");
	printf("\tLes   scripts   fournis   (update.sh,   debug.sh)   ne\n");
	printf("\tfonctionneront que  si la  norminette se  trouve de le\n");
	printf("\tdossier ~/norminette.  Vous pouvez sinon  les modifier\n");
	printf("\tpour les faire  fonctionner avec votre chemain d'accès\n");
	printf("\tN'hésitez pas à m'envoyer des suggestions par mail !\n");
	printf("MISES A JOUR :\n");
	printf("\tSi vous voulez recevoir des notifications de mises à\n");
	printf("\tjour, vous pouvez rejoindre de serveur : \n");
	printf("\thttps://discord.gg/RgDbJDW\n");
}

void	display_help(char *prog_name, int fr)
{
	addStackTraceEntry("display_help", "pb", "prog_name", prog_name, "fr", fr);
	if (fr)
		disp_fr_help(prog_name);
	else
		disp_en_help(prog_name);
	freeStackTrace();
	exit(0);
}

void	disp_list(list_t *list)
{
	addStackTraceEntry("disp_list", "p", "list", list);
	for (; list->next; list = list->next)
		printf("  -  '%s'\n", (char *)list->data);
	delStackTraceEntry();
}

flag	get_flags(int argc, char **args)
{
	flag	flags;
	int	disp = 0;
	char	*dir = 0;

	addStackTraceEntry("get_flags", "ip", "argc", argc, "args", args);
	memset(&flags, false, sizeof(flags));
	for (int i = 1; i < argc; i++)
		for (int j = 1; args[i][0] == '-' && args[i][j]; j++)
			if (args[i][j] == 'v')
				flags.v = 1;
			else if (args[i][j] == 's')
				flags.no_big_files = 1;
			else if (args[i][j] == 'l')
				flags.big_files = 1;
			else if (args[i][j] == 'f')
				flags.f = 1;
			else if (args[i][j] == 'u')
				flags.u = 1;
			else if (args[i][j] == 'n')
				flags.n = 1;
			else if (args[i][j] == 't')
				flags.t = 1;
			else if (args[i][j] == 'c')
				flags.c = 1;
			else if (args[i][j] == 'b') {
				flags.b = 1;
				if (!flags.b_fcts) {
					flags.b_fcts = my_malloc(sizeof(*flags.b_fcts));
					flags.b_fcts->next = 0;
					flags.b_fcts->prev = 0;
					flags.b_fcts->data = 0;
				}
			} else if (args[i][j] == 'a') {
				flags.u = 1;
				flags.v = 1;
				flags.i_caps = 1;
				flags.big_files = 1;
				load_functions(".", &flags);
				flags.b = 1;
				if (!flags.b_fcts) {
					flags.b_fcts = my_malloc(sizeof(*flags.b_fcts));
					flags.b_fcts->next = 0;
					flags.b_fcts->prev = 0;
					flags.b_fcts->data = 0;
				}
			} else if (args[i][j] == 'I') {
				dir = sub_strings(&args[i][j], 1, strlen(&args[i][j]) + 1, my_malloc(strlen(&args[i][j]) + 1));
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
				flags.t = 1;
			} else if (args[i][j] == 'h')
				disp = 1;
			else {
				printf("%s: Invalid option '%c' (ASCII : %i)\n", args[0], args[i][j], (unsigned char)args[i][j]);
				printf("Use « %s -h » for more informations\n", args[0]);
				free_list(flags.fcts);
				freeStackTrace();
				exit(84);
			}
	if (disp)
		display_help(args[0], flags.f);
	delStackTraceEntry();
	return (flags);
}
