/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:52:33 by jcollin           #+#    #+#             */
/*   Updated: 2022/03/26 11:35:50 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute(t_list *elem, t_fds *fds)
{
	pid_t	pid;
	int		exit_status;

	if (elem)
	{
		if (elem->next == NULL)
			ft_exec_cmd(elem, fds);
		else
		{
			pid = fork();
			if (!pid)
				ft_exec_pipes(elem, fds);
			ft_init_signal_handler(ft_handler_child);
			// wait(-1);
			waitpid(pid, &exit_status, 0);
			if (exit_status == 0)
				g_var->state = 0;
			if (WEXITSTATUS(exit_status))
				g_var->state = WEXITSTATUS(exit_status);
		}
	}
	else
		return ;
}
