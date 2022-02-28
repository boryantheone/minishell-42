#include "../minishell.h"

int	ft_echo(t_list *elem)
{
	int		i;
	int		j;
	int		flag_n;

	i = 0;
	flag_n = 0;
	if (!(ft_strncmp(elem->cmds[1], "-n", 2)))
	{
		flag_n = 1;
		i++;
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

int	ft_pwd(t_list *elem)
{
	char dir[MAXDIR];
	
	getcwd(dir, MAXDIR);
	ft_putstr_fd(dir, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(dir);
	return (EXIT_SUCCESS);
}

static int	ft_display_error(char *str)
{
	ft_putstr_fd("minishelchik: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
	return (EXIT_FAILURE);	
}

int	ft_cd_change_oldpwd(t_envp **env, char *prev_pwd)
{
	t_envp	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!(ft_strncmp(tmp->var, "OLDPWD", 6)))
		{
			tmp->val = prev_pwd;
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (EXIT_FAILURE);
}

int	ft_cd_change_pwd(char *new_pwd, char *prev_pwd, t_envp **env)
{
	t_envp	*tmp;

	tmp = *env;
	while (tmp)
	{
		if ((!ft_strncmp(tmp->var, "PWD", 3)))
		{
			tmp->val = new_pwd;
			if (chdir(new_pwd) == -1)
				return(ft_display_error(tmp->val));
		}
		tmp = tmp->next;
	}
	ft_cd_change_oldpwd(env, prev_pwd);
	free(tmp);
	ft_printlist_envp(*env);
	return (EXIT_FAILURE);
}

int	ft_cd(t_list *elem, t_var *var)
{
	char	prev_pwd[MAXDIR];
	char	*path;

	getcwd(prev_pwd, MAXDIR);
	if (!elem->cmds[1] || !(ft_strncmp(elem->cmds[1], "~", 1)))
		chdir(getenv("HOME")); //!!при парсинге обработать что если подается просто "cd" без пробела, то нужно записать пробел в cmds[1]
	if (!(ft_strncmp(elem->cmds[1], "/", 1)))
	{
		if (chdir(elem->cmds[1]) == -1)
			return(ft_display_error(elem->cmds[1]));
		else
		{
			write(1, "111", 1);
			ft_cd_change_pwd(elem->cmds[1], prev_pwd, &var->envp);
		}
	}
	return (EXIT_SUCCESS);
}

t_envp *ft_print_sorted_envp_list(t_envp *envp)
{
	t_envp *list_for_export;

	
}


int	ft_export(t_list *elem, t_envp *envp)
{
	if (elem->cmds[1] == NULL)
	{
		ft_print_sorted_envp_list();
	}
	printf("commanda export\n");
	return (0);
}

int	ft_unset(void)
{
	printf("commanda unset\n");
	return (0);
}

int	ft_env(t_list *elem, t_var *var)
{
	t_envp *tmp;

	if (elem->cmds[1])
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(elem->cmds[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	tmp = var->envp;
	while(tmp)
	{
		ft_putstr_fd(tmp->var, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(tmp->val, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_exit(t_list *elem)
{
	if (elem->have_pipe)
		return (EXIT_SUCCESS);
	ft_putendl_fd("exit", STDERR_FILENO);
	if (elem->cmds[1] == NULL || (ft_isdigit(elem->cmds[1]) && elem->cmds[2] == NULL))
		exit(EXIT_FAILURE);
	else if (ft_isdigit(elem->cmds[1]) && elem->cmds[2] != NULL)
		ft_putendl_fd("minishelchik: exit: too many arguments", STDERR_FILENO);
	else if (ft_isalpha(elem->cmds[1]))
	{
		ft_putstr_fd("minishelchik: exit: ", STDERR_FILENO);
		ft_putstr_fd(elem->cmds[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}