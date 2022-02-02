#include "../minishell.h"

// int	ft_exec_buildin(t_list *elem, t_var *var)
// {
// 	if (!ft_strncmp(elem->cmd, "pwd", 50000))
// 		return(ft_pwd());
// 	else if (!ft_strncmp(elem->cmd, "cd", 50000))
// 		return(ft_cd());
// 	else if (!ft_strncmp(elem->cmd, "echo", 50000))
// 		return(ft_echo());
// 	else if (!ft_strncmp(elem->cmd, "export", 50000))
// 		return(ft_export());
// 	else if (!ft_strncmp(elem->cmd, "unset", 50000))
// 		return(ft_unset());
// 	else if (!ft_strncmp(elem->cmd, "env", 50000))
// 		return(ft_env());
// 	else if (!ft_strncmp(elem->cmd, "exit", 50000))
// 		return(ft_exit());
// 	return (-1);
// }

// void	ft_exec_cmd(t_list *elem, t_var *var)
// {
// 	int		i;
// 	int		result;
// 	pid_t	pid;
// 	char	**cmd;

// 	i = 0;
// 	cmd = ft_split(elem->cmds, ' ');
// 	if ((result = ft_exec_buildin(elem, var)) >= 0)
// 		return (result);
// 	else
// 	{ 
// 		if ((pid = fork()) == 0)
// 		{
// 			if ((execve(elem->path, cmd, var->envp)) == -1)
// 			{
// 				perror("Error: ");
// 				exit(0);
// 			}
// 			exit(1);
// 		}
// 		waitpid(pid, NULL, 0);
// 	}
// 	return ;
// }