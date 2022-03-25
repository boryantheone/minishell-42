/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:19:15 by jcollin           #+#    #+#             */
/*   Updated: 2022/03/25 16:19:17 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execve_for_pipe(t_list *elem)
{
	char	**new_envp;

	if ((ft_exec_buildin(elem)) >= 0)
		exit(EXIT_SUCCESS);
	else
	{
		new_envp = ft_new_envp_for_execve();
		elem->path = ft_parsing_path(elem->cmd, new_envp);
		if (ft_is_a_directory(elem->path) == 1)
			ft_error_message_and_exit(127, elem->cmd, 1);
		if (ft_strcmp(elem->path, "command not found") == 0)
			ft_error_message_and_exit(127, elem->cmd, 0);
		execve(elem->path, elem->cmds, new_envp);
		ft_perror(elem->cmd, 1);
		ft_free(new_envp);
		exit(g_var->state);
	}
}

static void	ft_child_proc(int *fd, t_fds *fds)
{
	usleep(100);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	if (fds->next->fd_in != 0)
	{
		dup2(fds->next->fd_in, STDIN_FILENO);
		close(fds->next->fd_in);
	}
	close(fd[0]);
}

void	ft_launch_proc(t_list *elem, t_fds *fds)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
	{
		perror("minishelchik :");
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (fds->fd_out != 0)
		{
			dup2(fds->fd_out, STDOUT_FILENO);
			close(fds->fd_out);
		}
		close(fd[1]);
		execve_for_pipe(elem);
	}
	else
		ft_child_proc(fd, fds);
}

void	ft_wait(pid_t l_pid, int reserved_stdin, int reserved_stdout)
{
	pid_t	temp_pid;
	int		status;

	dup2(reserved_stdin, STDIN_FILENO);
	dup2(reserved_stdout, STDOUT_FILENO);
	close(reserved_stdin);
	close(reserved_stdout);
	temp_pid = waitpid(-1, &status, 0);
	while (temp_pid != -1)
	{
		if (temp_pid == l_pid)
			g_var->state = WEXITSTATUS(status);
		temp_pid = waitpid(-1, &status, 0);
	}
}

int	ft_exec_pipes(t_list *elem, t_fds *fds)
{
	pid_t	pid;
	t_list	*tmp;
	t_fds	*tmp_fds;
	int		reserved_stdout;
	int		reserved_stdin;

	reserved_stdin = dup(STDIN_FILENO);
	reserved_stdout = dup(STDOUT_FILENO);
	tmp = elem;
	tmp_fds = fds;
	ft_dup_fd_in(reserved_stdin, tmp_fds);
	while (tmp_fds->next != NULL)
	{
		ft_launch_proc(tmp, tmp_fds);
		tmp = tmp->next;
		tmp_fds = tmp_fds->next;
	}
	ft_dup_fd_out(reserved_stdout, tmp_fds);
	g_var->state = execve_for_pipe(tmp);
	ft_wait(pid, reserved_stdin, reserved_stdout);
	return (g_var->state);
}
