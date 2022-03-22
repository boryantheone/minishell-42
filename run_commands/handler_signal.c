#include "minishell.h"

void ft_handler_signal(int sig)
{
	struct sigaction act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = hdl;
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTSTP);
	sigaddset(&set, SIGQUIT);
	act.sa_mask = set;
	sigaction(SIGINT, &act, 0);
	sigaction(SIGTSTP, &act, 0);
	sigaction(SIGQUIT, &act, 0);
}