#include "../minishell.h"

int	ft_exec_buildin(t_list *elem, t_var *var)
{
	if (!ft_strncmp(elem->cmd, "pwd", 50000))
		return(ft_pwd());
	else if (!ft_strncmp(elem->cmd, "cd", 50000))
		return(ft_cd());
	else if (!ft_strncmp(elem->cmd, "echo", 50000))
		return(ft_echo());
	else if (!ft_strncmp(elem->cmd, "export", 50000))
		return(ft_export());
	else if (!ft_strncmp(elem->cmd, "unset", 50000))
		return(ft_unset());
	else if (!ft_strncmp(elem->cmd, "env", 50000))
		return(ft_env());
	else if (!ft_strncmp(elem->cmd, "exit", 50000))
		return(ft_exit());
	return (-1);
}

int	ft_exec_cmd(t_list *elem, t_var *var)
{
	int		i;
	int		result;
	pid_t	pid;
	char	**cmd;

	i = 0;
	cmd = ft_split(elem->cmds, ' ');
	if ((result = ft_exec_buildin(elem, var)) >= 0)
		return (result);
	else
	{ 
		if ((pid = fork()) == 0)
		{
			if ((execve(elem->path, cmd, var->envp)) == -1)
			{
				perror("Error: ");
				exit(0);
			}
			exit(1);
		}
		waitpid(pid, NULL, 0);
	}
	return (0);
}

void	execve_for_pipe(t_list *elem,t_var *var)
{
	char **cmds;

	write(1, "execve_for_pipe\n", 17);
	cmds = ft_split(elem->cmds, ' ');
	if ((ft_exec_buildin(elem, var)) >= 0)
		exit(1);
	else
		execve(elem->path, cmds, var->envp);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(elem->cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(1);
}

void	ft_launch_child_proc_for_pipe(t_var *var, t_list *elem, int	fd_close)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
	{
		perror("Error :");
		exit(1);
		///free all
	}
	write(1, "launch\n", 8);
	if ((pid = fork()) == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		write(1, "anoba\n", 7);
		if (fd_close != -1)
			dup2(fd_close, STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		execve_for_pipe(elem, var);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		write(1, &elem->next->cmd, 4);
		if (elem->next->fd_open != -1)
			dup2(elem->next->fd_open, STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
}

int ft_exec_pipes(t_var *var, t_list **elem)
{
	int	i;
	t_list	*tmp;
	int		fd_close;

	i = 0;
	tmp = *elem;
	write(1, "1111", 4);
	if (tmp->fd_open != -1)
		dup2(tmp->fd_open, STDIN_FILENO);
	else
		dup2(0, STDIN_FILENO);
	var->size_of_list = ft_lstsize(tmp);
	write(1, "2222\n", 4);
	write(1, tmp->cmd, 2);
	write(1, "\n", 1);
	while (i < var->size_of_list - 1)
	{
		fd_close = tmp->fd_close;
		write(1, "sdsds\n", 6);
		tmp = tmp->next;
		write(1, "next\n", 6);
		ft_launch_child_proc_for_pipe(var, tmp, fd_close);
		i++;
	}
	write(1, "3333", 4);
	//tmp = tmp->next;
	if (tmp->fd_close != -1)
		dup2(tmp->fd_close, STDOUT_FILENO);
	else
		dup2(1, STDOUT_FILENO);
	return (1);
}

