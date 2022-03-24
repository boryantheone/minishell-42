#include "../minishell.h"

void	ft_child_sigint(void)
{
	int		exit_status;
	pid_t	pid;

	pid = waitpid(-1, &exit_status, 0);
	g_var->state = 130;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ft_child_sigquit(void)
{
	int		exit_status;
	pid_t	pid;

	pid = waitpid(-1, &exit_status, 0);
	g_var->state = 131;
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
}

void	ft_handler_child(int sig)
{	
	if (sig == SIGINT)
		ft_child_sigint();
	if (sig == SIGQUIT)
		ft_child_sigquit();
}

void	ft_handler_ctrl_d(void)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	ft_handler_sigint(void)
{
	g_var->state = 1;
	rl_on_new_line();
	ft_putstr_fd("\n", STDIN_FILENO);
	rl_redisplay();
}

void	ft_handler_main(int sig)
{
	if (sig == SIGINT)
		ft_handler_sigint();
}

void	ft_init_signal_handler(void (*ft_handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = ft_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
