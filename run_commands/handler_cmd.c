#include "../minishell.h"


int	ft_exec_buildin(t_list *elem, t_var *var)
{
	
	if (!ft_strcmp(elem->cmd, "pwd"))
		return(ft_pwd(elem));
	else if (!ft_strcmp(elem->cmd, "cd"))
		return(ft_cd(elem, var));
	else if (!ft_strcmp(elem->cmd, "echo"))
		return(ft_echo(elem));
	else if (!ft_strcmp(elem->cmd, "export"))
		return(ft_export(elem, var));
	else if (!ft_strcmp(elem->cmd, "unset"))
		return(ft_unset(var, elem));
	else if (!ft_strcmp(elem->cmd, "env"))
		return(ft_env(elem, var));
	else if (!ft_strcmp(elem->cmd, "exit"))
		return(ft_exit(elem));
	return (-1);
}

int	ft_return_child_exit_status(pid_t pid, t_fds *fds, int reserved_stdout, int
reserved_stdin)
{
	int	exit_status;
	int	error_state;
	
	dup2(reserved_stdin, STDIN_FILENO);
	close(reserved_stdin);
	dup2(reserved_stdout, STDOUT_FILENO);
	close(reserved_stdout);
	waitpid(pid, &exit_status, 0);
	if (exit_status == 0)
		return (0);
	if (WIFSIGNALED(exit_status))
		return(128 + exit_status);
	error_state = WEXITSTATUS(exit_status);
	
	return (error_state);
}

int	ft_lstsize_envp(t_envp *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		i++;
		lst = lst -> next;
	}
	return (i);
}

char	**ft_new_envp_for_execve(void)
{
	t_envp *old_envp;
	int		i;
	char	**new_envp;
	char	*tmp;

	i = 0;
	old_envp = var->envp;
	new_envp = (char **)malloc(sizeof(char *) * ((ft_lstsize_envp(old_envp)) +
			1));
	while (old_envp != NULL)
	{
		tmp = ft_strjoin(old_envp->var, "=");
		new_envp[i] = ft_strjoin(tmp, old_envp->val);
		i++;
		free(tmp);
		old_envp = old_envp->next;
		free(tmp);
	}
	new_envp[i] = NULL;
	return (new_envp);
}

int	ft_is_a_directory(char *cmd)
{
	struct stat dir;

	stat(cmd, &dir);
	return(S_ISDIR(dir.st_mode));
}

void	ft_error_message_and_exit(int exit_status, char *cmd, int choice)
{
	ft_putstr_fd("minishelchik: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	if (choice == 0)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else if (choice == 1)
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	var->state = exit_status;
	exit(exit_status);
	exit(0);
}

void	 ft_execute_terminal_cmd(t_list *elem, t_fds *fds, int reserved_stdout, int reserved_stdin)
{
	pid_t	pid;
	char	**new_envp;

	pid = fork();
	if (pid == 0)
	{
		if ((execve(elem->path, elem->cmds, new_envp)) == -1)
		{
			ft_display_error(elem->cmd, elem->path);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
		new_envp = ft_new_envp_for_execve();
		elem->path = ft_parsing_path(elem->cmd, new_envp);
		if (ft_is_a_directory(elem->path) == 1)
			ft_error_message_and_exit(127, elem->cmd, 1);
		if (ft_strcmp(elem->path, "command not found") == 0)
			ft_error_message_and_exit(127, elem->cmd, 0);
		execve(elem->path, elem->cmds, new_envp);
		ft_perror(elem->cmd, 1);
		exit(var->state);
	}
	else
		var->state = ft_return_child_exit_status(pid, fds, reserved_stdout,
												 reserved_stdin);
}

int	ft_exec_cmd(t_list *elem, t_var *var, t_fds *fds)
{
	int		result;
	int		reserved_stdout;
	int		reserved_stdin;
	char	**new_envp;
	
	reserved_stdout = dup(STDOUT_FILENO);
	reserved_stdin = dup(STDIN_FILENO);
	if (ft_check_fds(fds) != -1)
	{
		if (fds->fd_in != 0)
		{
			dup2(fds->fd_in, STDIN_FILENO);
			close(fds->fd_in);
		}
		if (fds->fd_out != 0)
		{
			dup2(fds->fd_out, STDOUT_FILENO);
			close(fds->fd_out);
		}
	}
	if ((result = ft_exec_buildin(elem, var)) >= 0)
		return (result);
	else
	{

		new_envp = ft_new_envp_for_execve();
		elem->path = ft_parsing_path(elem->cmd, new_envp);
		if (ft_strcmp(elem->path, "command not found") == 0)
		{
			ft_display_error(elem->cmd, elem->path);
			return (EXIT_FAILURE);
		}
		ft_execute_terminal_cmd(elem, new_envp, fds, reserved_stdout,
								reserved_stdin);
	}
	return (EXIT_SUCCESS);
}