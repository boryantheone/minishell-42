#include "../minishell.h"

void	ft_exec_cmd(t_var *var)
{
	int	i;
	pid_t	pid;
	char	**cmd;

	i = 0;
	cmd = ft_split(var->elem->cmds, ' ');
	if ((pid = fork()) == 0)
	{
		if ((execve(var->elem->path, cmd, var->envp)) == -1)
		{
			perror("Error: ");
			exit(0);
		}
		exit(1);
	}
	waitpid(pid, NULL, 0);
}

void ft_exec_pipes(t_var *var)
{
	int	i;

	i = 0;
	var->size_of_list = ft_lstsize(var->elem);
	
	while (i < var->size_of_list)
	{
		ft_exec_cmd(var);
		var->elem = var->elem->next;
		i++;
	}
}