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
		free(path);
		if (access(cmdpath, R_OK) == 0)
		{
			ft_free(paths);
			return (cmdpath);
		}
		free(cmdpath);
		i++;
	}
	ft_free(paths);
	return ("command not found");
}

void	execve_for_pipe(t_list *elem,t_var *var)
{
	if ((ft_exec_buildin(elem, var)) >= 0)
		exit(EXIT_SUCCESS);
	else
	{
		if ((execve(elem->path, elem->cmds, var->envp_for_execve)) == -1)
		{
			perror("Error: ");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}

}

void	ft_launch_proc(t_var *var, t_list *elem, t_fds *fds, int i, \
						int reserved_stdout, int reserved_stdin)
{
	int		fd[2];
	pid_t	pid;

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
		if (fds->fd_out != 0)
		{
			dup2(fds->fd_out, STDOUT_FILENO);
			close(fds->fd_out);
		}
		close(fd[1]);
		execve_for_pipe(elem, var);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		if (fds->next->fd_in != 0)
		{
			dup2(fds->next->fd_in, STDIN_FILENO);
			close(fds->next->fd_in);
		}
		close(fd[0]);
	}
}

int  ft_exec_pipes(t_var *var, t_list *elem, t_fds *fds)
{
	t_list	*tmp;
	int		status;
	t_fds	*tmp_fds;
	int		reserved_stdout;
	int		reserved_stdin;
	int 	i;
	int		fd;
	pid_t	pidor;
	pid_t 	pid;
	
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
	else
		dup2(reserved_stdin, STDIN_FILENO);
	while (tmp_fds->next != NULL)
	{
		tmp->path = ft_parsing_path(tmp->cmd, var->envp_for_execve);
		ft_launch_proc(var, tmp, tmp_fds, i, \
			reserved_stdout, reserved_stdin);
		tmp = tmp->next;
		tmp_fds = tmp_fds->next;
		i++;
	}
//	if (tmp_fds->fd_in != 0)
//	{
//		write(1, "change fd_in\n", 13);
//		dup2(tmp_fds->fd_in, STDIN_FILENO);
//		close(tmp_fds->fd_in);
//	}
//	else
//		dup2(fd, STDIN_FILENO);
	dup2(reserved_stdout, STDOUT_FILENO);
	if (tmp_fds->fd_out != 0)
	{
		dup2(tmp_fds->fd_out, STDOUT_FILENO);
		close(tmp_fds->fd_out);
	}
	tmp->path = ft_parsing_path(tmp->cmd, var->envp_for_execve);
	execve_for_pipe(tmp, var);
	dup2(reserved_stdin, STDIN_FILENO);
	dup2(reserved_stdout, STDOUT_FILENO);
	close(reserved_stdin);
	close(reserved_stdout);
	pidor = waitpid(-1, &status, 0);
	while (pidor != -1)
		pidor = waitpid(-1, &status, 0);
	return (EXIT_SUCCESS);
}

