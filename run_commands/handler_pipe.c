#include "../minishell.h"
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
		if ((access(cmdpath, 0) == 0) && (access(cmdpath, 1) == 0))
		{
			//ft_free(paths);
			return (cmdpath);
		}
		i++;
	}
	//ft_free(paths);
	return (0);
}

void	ft_exec_cmd(char **cmd, char **env)
{
	int	i;
	pid_t	pid;
	char	**cmd;

	i = 0;
	cmd = ft_split(var->cmd[0], ' ');
	pid = fork();
	if ((pid = fork()) == 0)
	{
		if ((execve(ft_parsing_path(cmd[0], env), cmd, env)) == -1)
		{
			perror("Error: ");
			exit(0);
		}
		exit(1);
	}	
	else
		printf("error");
}



int	main(int argc, char **argv, char **env)
{
	t_var	*var;


	if (argc == 0)
		printf("error");
	if (!(var = (t_var *)malloc(sizeof(t_var))))
		return(0); //malloc error
	var->cmd[0] = argv[1];
	ft_exec_cmd(var->cmd, env);
}