/*
** EPITECH PROJECT, 2017
** catch_sig
** File description:
** Function which will be called if a fatal signal is recieved
*/

#include "functions.h"
#include "stacktrace.h"
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int	signal_caught = 0;

void	catch_sig(int sig_ID, siginfo_t *infos, void *ptr)
{
	signal_caught++;
	if (sig_ID == 2) {
		printf("\rInterrupted.\n");
		display_result(get_mistakes(), get_flags_var());
	} else if (sig_ID == 15) {
		printf("\rTerminated.\n");
		display_result(get_mistakes(), get_flags_var());
	} else {
		if (signal_caught >= 2) {
			printf("\nHum, that's embarrassing...\n");
			printf("Recieved signal %i (%s)\n", sig_ID, strsignal(sig_ID));
		} else {
			printf("\n\nOops !\nSomething went wrong...\n");
			printf("Program killed by signal %i (%s)", sig_ID, strsignal(sig_ID));
			printf(" dumping core");
			if (infos->si_errno)
				printf(" : \"%s\"", strerror(infos->si_errno));
			printf("\nPlease report this error\n");
			printStackTrace();
			freeStackTrace();
			(void)ptr;
		}
		exit(128 + sig_ID);
	}
}
