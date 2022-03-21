#include "../minishell.h"

int	ft_echo(t_list *elem)
{
	int	i;
	int	j;
	int	flag_n;
	
	i = 0;
	flag_n = 0;
	var->state = 0;
	if (elem->cmds[1] != NULL)
	{
		if (!(ft_strncmp(elem->cmds[1], "-n", 2)))
		{
			flag_n = 1;
			i++;
		}
	}
	while (elem->cmds[++i] != NULL)
	{
		ft_putstr_fd(elem->cmds[i], STDOUT_FILENO);
		if (elem->cmds[i + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!flag_n)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

int ft_pwd(t_list *elem)
{
	char dir[MAXDIR];
	
	getcwd(dir, MAXDIR);
	ft_putstr_fd(dir, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	var->state = 0;
	return (EXIT_SUCCESS);
}

int	ft_exit(t_list *elem)
{
	var->state = 0;
	if (elem->next)
		return (EXIT_SUCCESS);
	ft_putendl_fd("exit", STDERR_FILENO);
	if (elem->cmds[1] == NULL || (ft_isdigit(elem->cmds[1]) && elem->cmds[2] == NULL))
		exit (EXIT_FAILURE);
	else if (ft_isdigit(elem->cmds[1]) && elem->cmds[2] != NULL)
	{
		var->state = 1;
		ft_putendl_fd("minishelchik: exit: too many arguments", STDERR_FILENO);
	}
	else if (ft_isalpha(elem->cmds[1]))
	{
		ft_putstr_fd("minishelchik: exit: ", STDERR_FILENO);
		ft_putstr_fd(elem->cmds[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_env(t_list *elem, t_var *var)
{
	t_envp	*tmp;
	
	tmp = var->envp;
	if (elem->cmds[1])
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(elem->cmds[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		var->state = 127;
		exit(EXIT_FAILURE);
	}
	while (tmp)
	{
		if (tmp->val != NULL && tmp->var != NULL)
		{
			ft_putstr_fd(tmp->var, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(tmp->val, STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
		}
		tmp = tmp->next;
	}
	var->state = 0;
	return (EXIT_SUCCESS);
}
