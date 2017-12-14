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
		my_printf("\t\tvaleur l'erreur\n\n");
		my_printf("RAPPORTER UN BUG :\n");
		my_printf("\tSi vous  trouvez un bug, mettez  à jour  le  programme\n");
		my_printf("\t(Utilisez le script 'update.sh' dans le repo ou encore\n");
		my_printf("\t<votre alias>-update  si vous  avez utilisé  le script\n");
		my_printf("\td'installation). Si le bug persiste, lancez 'debug.sh'\n");
		my_printf("\t(<votre alias>-debug) avec, comme argument, le fichier\n");
		my_printf("\tayant causé  le bug. Envoyez moi  ensuite  le  fichier\n");
		my_printf("\tscan.log (vous pouvez aussi  joindre le fichier posant\n");
		my_printf("\tproblème)   à   l'addresse  \"andgel.halley@epitech.eu\"\n");
		my_printf("\ten expliquant  le bug rencontrez  et je le  corrigerai\n");
		my_printf("\tle plus vite possible !\n\n");
		my_printf("\tNote : Inutile de le lancer en mode debug si  ce n'est\n");
		my_printf("\tqu'un problème d'affichage (faute de frappe, ...)\n");
		my_printf("\tLes   scripts   fournis   (update.sh,   debug.sh)   ne\n");
		my_printf("\tfonctionneront que  si la  norminette se  trouve de le\n");
		my_printf("\tdossier ~/norminette.  Vous pouvez sinon  les modifier\n");
		my_printf("\tpour les faire  fonctionner avec votre chemain d'accès\n");
		my_printf("\tN'hésitez pas à m'envoyer des suggestions par mail !\n");
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
		my_printf("REPORT A BUG :\n");
		my_printf("\tIf you find a bug, first, update  the program  (Use the\n");
		my_printf("\t'update.sh'  in  the  repository or, if  you  used  the\n");
		my_printf("\tinstallation script, <your alias>-update). If it is not\n");
		my_printf("\tyet patched, run the 'debug.sh' (or <your alias>-debug)\n");
		my_printf("\twith,  as argument, the  file  which caused  the bug to\n");
		my_printf("\thappen. Send me, then, the  scan.log file (you can join\n");
		my_printf("\tthe source  file too) at  \"andgel.halley@epitech.eu\".\n");
		my_printf("\tExplain briefly in the mail what happened and  I'll fix\n");
		my_printf("\tas fast as I can !\n\n");
		my_printf("\tNote : No need to launch  in debug mode if  it's just a\n");
		my_printf("\tdisplay problem (spelling mistake, ...).\n");
		my_printf("\tThe given scripts (update.sh, debug.sh) will only work\n");
		my_printf("\tif the program is stored in ~/norminette. You can also\n");
		my_printf("\tmodify  the scripts  to make them  work with your  own\n");
		my_printf("\tpath\n");
		my_printf("\tYou can also send me ideas by mail !\n");
	}
	exit(0);
}

flag	get_flags(int argc, char **args)
{
	flag	flags = {0, 0, 0, 0, 0};
	int	disp = 0;

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
			} else if (args[i][j] == 'd') {
				flags.n = 1;
				flags.d = 1;
			} else if (args[i][j] == 'h')
				disp = 1;
			else {
				my_printf("%s: Invalid option '%c'\n", args[0], args[i][j]);
				my_printf("Use « %s -h » for more informations\n", args[0]);
				exit(84);
			}
	if (disp)
		display_help(args[0], flags.f);
	return (flags);
}
