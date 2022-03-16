#include "../minishell.h"

void	ft_free(char **dst)
{
	size_t	i;
	
	i = 0;
	while (dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
}

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

char	*ft_parsing_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmdpath;
	char	*path;
	int		i;
	
	i = 0;
	while (envp[i] != ft_strnstr(envp[i], "PATH=", 5))
		i++;
	path = envp[i];
	i = 0;
	paths = ft_split(path + 5, ':');
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmdpath = ft_strjoin(path, cmd);
		if (access(cmdpath, 0) == 0)
		{
//			ft_free(paths);
			return (cmdpath);
		}
		i++;
	}
	//ft_free(paths);
	return (0);
}

int	ft_exec_cmd(t_list *elem, t_var *var, t_fds *fds)
{
	int		i;
	int		result;
	pid_t	pid;

	i = 0;
	elem->path = ft_parsing_path(elem->cmd, var->envp_for_execve);
	printf("path %s\n", elem->path);
	if (fds->fd_in != 0)
		dup2(fds->fd_in, STDIN_FILENO);
	if (fds->fd_out != 0)
		dup2(fds->fd_out, STDOUT_FILENO);
	if ((result = ft_exec_buildin(elem, var)) >= 0)
		return (result);
	else
	{ 
		if ((pid = fork()) == 0)
		{
			if ((execve(elem->path, elem->cmds, var->envp_for_execve)) == -1)
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
	if ((ft_exec_buildin(elem, var)) >= 0)
		exit(1);
	else
		execve(elem->path, elem->cmds, var->envp_for_execve);
	exit(EXIT_SUCCESS);
}

void	ft_launch_proc(t_var *var, t_list *elem)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) < 0)
	{
		perror("Error :");
		exit(1);
		///free all
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve_for_pipe(elem, var);
	}
	waitpid(-1, &status, 0);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
}

int ft_exec_pipes(t_var *var, t_list *elem, t_fds *fds)
{
	int		i;
	t_list	*tmp;
	int		fd_close;
	int		status;
	t_fds	*tmp_fds;

	i = 0;
	tmp = elem;
	tmp_fds = fds;
	if (tmp_fds->fd_in != 0)
		dup2(tmp_fds->fd_in, STDIN_FILENO);
	while (tmp_fds->next != NULL)
	{
		tmp->path = ft_parsing_path(tmp->cmd, var->envp_for_execve);
		ft_launch_proc(var, tmp);
		tmp = tmp->next;
		tmp_fds = tmp_fds->next;
	}
	if (tmp_fds->fd_out != 0)
		dup2(tmp_fds->fd_out, STDIN_FILENO);
	tmp->path = ft_parsing_path(tmp->cmd, var->envp_for_execve);
	execve_for_pipe(tmp, var);
	waitpid(-1, &status, 0);
	// if (WIFEXITED(status))
	write(1, "3333", 4);
	return (1);
	//exit(EXIT_SUCCESS);
}

