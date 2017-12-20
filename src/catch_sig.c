/*
** EPITECH PROJECT, 2017
** catch_sig
** File description:
** Function which will be called if a fatal signal is recieved
*/

#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char	*getsig_name(int sig_ID)
{
	switch(sig_ID) {
	case 4:
		return ("SIGILL");
	case 5:
		return ("SIGTRAP");
	case 6:
		return ("SIGABRT");
        case 11:
		return ("SIGSEGV");
	}
	return ("??");
}

void	catch_sig(int sig_ID, siginfo_t *infos, void *ptr)
{
	if (sig_ID == 2) {
		printf("Interrupted.\n");
		exit(84);
	} else {
		printf("\n\nOops !\nSomething went wrong...\n");
		printf("Program killed by signal %i (%s)", sig_ID, getsig_name(sig_ID));
		printf(" dumping core\n");
		if (infos->si_errno)
			printf("\"%s\"\n", strerror(infos->si_errno));
		printf("Pls report this error\n");
		(void)ptr;
		exit(128 + sig_ID);
	}
}
