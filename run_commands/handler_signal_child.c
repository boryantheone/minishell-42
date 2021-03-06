/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal_child.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:20:43 by jcollin           #+#    #+#             */
/*   Updated: 2022/03/26 12:51:56 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handler_heredoc(int sig)
{
	int		exit_status;
	int		pid;

	pid = waitpid(-1, &exit_status, 0);
	g_var->state = 1;
	signal(SIGINT, SIG_DFL);
	exit(g_var->state);
}

void	ft_child_sigint(void)
{
	int		exit_status;
	int		pid;

	pid = waitpid(-1, &exit_status, 0);
	g_var->state = 130;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ft_child_sigquit(void)
{
	int		exit_status;
	int		pid;

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
