/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:49:49 by jcollin           #+#    #+#             */
/*   Updated: 2022/03/25 15:50:18 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exec_buildin(t_list *elem)
{
	if (!ft_strcmp(elem->cmd, "pwd"))
		return (ft_pwd(elem));
	else if (!ft_strcmp(elem->cmd, "cd"))
		return (ft_cd(elem));
	else if (!ft_strcmp(elem->cmd, "echo"))
		return (ft_echo(elem));
	else if (!ft_strcmp(elem->cmd, "export"))
		return (ft_export(elem));
	else if (!ft_strcmp(elem->cmd, "unset"))
		return (ft_unset(elem));
	else if (!ft_strcmp(elem->cmd, "env"))
		return (ft_env(elem));
	else if (!ft_strcmp(elem->cmd, "exit"))
		return (ft_exit(elem));
	return (-1);
}

int	ft_return_child_exit_status(pid_t pid, t_fds *fds, int reserved_stdout, int
reserved_stdin)
{
	int	exit_status;

	dup2(reserved_stdin, STDIN_FILENO);
	close(reserved_stdin);
	dup2(reserved_stdout, STDOUT_FILENO);
	close(reserved_stdout);
	waitpid(pid, &exit_status, 0);
	if (WEXITSTATUS(exit_status))
		g_var->state = WEXITSTATUS(exit_status);
	return (g_var->state);
}

char	**ft_new_envp_for_execve(void)
{
	t_envp	*old_envp;
	int		i;
	char	**new_envp;
	char	*tmp;

	i = 0;
	old_envp = g_var->envp;
	new_envp = (char **)malloc(sizeof(char *) * \
	((ft_lstsize_envp(old_envp)) + 1));
	while (old_envp != NULL)
	{
		tmp = ft_strjoin(old_envp->var, "=");
		new_envp[i] = ft_strjoin(tmp, old_envp->val);
		i++;
		free(tmp);
		old_envp = old_envp->next;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	ft_execute_terminal_cmd(t_list *elem, t_fds *fds, \
int reserved_stdout, int reserved_stdin)
{
	pid_t	pid;
	char	**new_envp;

	pid = fork();
	if (pid == 0)
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
	else
	{
		ft_init_signal_handler(ft_handler_child);
		g_var->state = ft_return_child_exit_status(pid, fds, reserved_stdout, \
		reserved_stdin);
	}
}

int	ft_exec_cmd(t_list *elem, t_fds *fds)
{
	int		result;
	int		reserved_stdout;
	int		reserved_stdin;

	reserved_stdout = dup(STDOUT_FILENO);
	reserved_stdin = dup(STDIN_FILENO);
	if (ft_check_fds(fds) != -1)
		ft_dup_fd_in_out(&fds);
	else
		return (EXIT_FAILURE);
	result = ft_exec_buildin(elem);
	if (result >= 0)
		return (result);
	else
		ft_execute_terminal_cmd(elem, fds, reserved_stdout, reserved_stdin);
	return (EXIT_SUCCESS);
}
