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
		if (access(cmdpath, R_OK) == 0)
			return (cmdpath);
		i++;
	}
	return ("command not found");
}
void	execve_for_pipe(t_list *elem,t_var *var)
{
	if ((ft_exec_buildin(elem, var)) >= 0)
		exit(1);
	else
		if ((execve(elem->path, elem->cmds, var->envp_for_execve)) == -1)
		{
			perror("Error: ");
			exit (EXIT_FAILURE);
		}
	exit(EXIT_SUCCESS);
}

void	ft_launch_proc(t_var *var, t_list *elem, t_fds *fds, int i)
{
	int		fd[2];
	pid_t	pid;
	int		status;
	int 	reserved_stdin;

	reserved_stdin = dup(STDIN_FILENO);
	if (pipe(fd) < 0)
	{
		perror("Error :");
		exit(1);
		///free all
	}
	pid = fork();
	if (pid == 0)
	{
		if (fds->fd_out != 0)
		{
			dup2(fds->fd_out, STDOUT_FILENO);
			close(fds->fd_out);
		}
		else
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		execve_for_pipe(elem, var);
	}
	if (fds->fd_in != 0)
	{
		dup2(fds->fd_in, STDIN_FILENO);
		close(fds->fd_in);
	}
	else
		dup2(fd[0], STDIN_FILENO);
//	dup2(reserved_stdin, STDIN_FILENO);
//	close(fd[1]);
	close(fd[0]);
	close(fd[1]);
}

int  ft_exec_pipes(t_var *var, t_list *elem, t_fds *fds)
{
	t_list	*tmp;
	int		status;
	t_fds	*tmp_fds;
	int		reserved_stdout;
	int		reserved_stdin;
	int 	i;
	
	reserved_stdin = dup(STDIN_FILENO);
	reserved_stdout = dup(STDOUT_FILENO);
	tmp = elem;
	tmp_fds = fds;
	i = 0;
	if (fds->fd_in != 0)
	{
		dup2(fds->fd_in, STDIN_FILENO);
		close(fds->fd_in);
	}
	while (tmp_fds->next != NULL)
	{
		tmp->path = ft_parsing_path(tmp->cmd, var->envp_for_execve);
		ft_launch_proc(var, tmp, tmp_fds, i);
		tmp = tmp->next;
		tmp_fds = tmp_fds->next;
		i++;
	}
	tmp->path = ft_parsing_path(tmp->cmd, var->envp_for_execve);
	execve_for_pipe(tmp, var);
	dup2(reserved_stdin, STDIN_FILENO);
	waitpid(-1, &status, 0);
	write(1, "finish\n", 7);
	return (1);
	//exit(EXIT_SUCCESS);
}

