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
	if (cmd == NULL || ft_strchr(cmd, '/') != 0)
		return (cmd);
	while (envp[i] && envp[i] != ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if ((ft_strnstr(envp[i], "PATH=", 5)) == NULL)
		return ("command not found");
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

void	execve_for_pipe(t_list *elem)
{
	char **new_envp;

	if ((ft_exec_buildin(elem, var)) >= 0)
		exit(EXIT_SUCCESS);
	else
	{
		new_envp = ft_new_envp_for_execve();
		elem->path = ft_parsing_path(elem->cmd, new_envp);
		if (ft_strcmp(elem->path, "command not found") == 0)
			ft_error_message_and_exit(127, elem->cmd, 0);
		execve(elem->path, elem->cmds, new_envp);
		ft_perror(elem->cmd, 1);
		ft_free(new_envp);
		exit(var->state);
	}
}

void	ft_launch_proc(t_list *elem, t_fds *fds, int i, \
						int reserved_stdout, int reserved_stdin)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
	{
		perror("minishelchik :");
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
		execve_for_pipe(elem);
	}
	else
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
		ft_launch_proc(tmp, tmp_fds, i, \
			reserved_stdout, reserved_stdin);
		tmp = tmp->next;
		tmp_fds = tmp_fds->next;
		i++;
	}
	dup2(reserved_stdout, STDOUT_FILENO);
	if (tmp_fds->fd_out != 0)
	{
		dup2(tmp_fds->fd_out, STDOUT_FILENO);
		close(tmp_fds->fd_out);
	}
	execve_for_pipe(tmp);
	dup2(reserved_stdin, STDIN_FILENO);
	dup2(reserved_stdout, STDOUT_FILENO);
	close(reserved_stdin);
	close(reserved_stdout);
	pid = waitpid(-1, &status, 0);
	while (pid != -1)
		pid = waitpid(-1, &status, 0);
	return (EXIT_SUCCESS);
}

