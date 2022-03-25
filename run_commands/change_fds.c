/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:21:43 by jcollin           #+#    #+#             */
/*   Updated: 2022/03/25 16:21:44 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup_fd_in(int reserved_stdin, t_fds *fds)
{
	if (fds->fd_in != 0)
	{
		dup2(fds->fd_in, STDIN_FILENO);
		close(fds->fd_in);
	}
	else
		dup2(reserved_stdin, STDIN_FILENO);
}

void	ft_dup_fd_out(int reserved_stdout, t_fds *fds)
{
	dup2(reserved_stdout, STDOUT_FILENO);
	if (fds->fd_out != 0)
	{
		dup2(fds->fd_out, STDOUT_FILENO);
		close(fds->fd_out);
	}
}
