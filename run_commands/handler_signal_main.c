/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:20:49 by jcollin           #+#    #+#             */
/*   Updated: 2022/03/26 12:45:02 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handler_ctrl_d(void)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	ft_handler_sigint(void)
{
	// void (sig);
	// if (sig == SIGINT)
	// {
		g_var->state = 1;
		rl_on_new_line();
		ft_putstr_fd("\n", STDIN_FILENO);
		rl_redisplay();
	// }
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
		// rl_on_new_line();
		// rl_redisplay();
		// write(2, "  \n", 3);
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		// g_var->state = 1;
}

void	ft_do_nothing(void)
{
	rl_on_new_line();
	rl_redisplay();
	// rl_redisplay();
	// write(2, "  \n", 3);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
}

void	ft_handler_main(int sig)
{
	if (sig == SIGINT)
		ft_handler_sigint();
	if (sig == SIGQUIT)
		signal(SIGQUIT, SIG_IGN);
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
