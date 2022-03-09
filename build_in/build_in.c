#include "../minishell.h"

int ft_echo(t_list *elem)
{
	int i;
	int j;
	int flag_n;

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

int ft_pwd(t_list *elem)
{
	char dir[MAXDIR];

	getcwd(dir, MAXDIR);
	ft_putstr_fd(dir, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(dir);
	return (EXIT_SUCCESS);
}

static int ft_display_error(char *str)
{
	ft_putstr_fd("minishelchik: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
	return (EXIT_FAILURE);
}

int ft_cd_change_oldpwd(t_envp **env, char *prev_pwd)
{
	t_envp *tmp;

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

int ft_cd_change_pwd(char *new_pwd, char *prev_pwd, t_envp **env)
{
	t_envp *tmp;
	char pwd[MAXDIR];

	tmp = *env;
	while (tmp)
	{
		if ((!ft_strncmp(tmp->var, "PWD", 3)))
		{
			getcwd(pwd, MAXDIR);
			if (chdir(new_pwd) == -1)
				return (ft_display_error(tmp->val));
			if (!(ft_strcmp(new_pwd, "..")))
				tmp->val = pwd;
			else
				tmp->val = new_pwd;
		}
		tmp = tmp->next;
	}
	ft_cd_change_oldpwd(env, prev_pwd);
	free(tmp);
	ft_printlist_envp(*env);
	return (EXIT_FAILURE);
}

int ft_cd(t_list *elem, t_var *var)
{
	char prev_pwd[MAXDIR];
	char *path;

	getcwd(prev_pwd, MAXDIR);
	printf("prewpwd = %s", prev_pwd);
	if (!elem->cmds[1] || !(ft_strncmp(elem->cmds[1], "~", 1)))
		chdir(getenv("HOME")); //!!при парсинге обработать что если подается просто "cd" без пробела, то нужно записать пробел в cmds[1]
	if (!(ft_strncmp(elem->cmds[1], "/", 1)) || !(ft_strcmp(elem->cmds[1], "..")))
	{
		if (chdir(elem->cmds[1]) == -1)
			return (ft_display_error(elem->cmds[1]));
		else
			ft_cd_change_pwd(elem->cmds[1], prev_pwd, &var->envp);
	}
	return (EXIT_SUCCESS);
}

static t_envp *ft_lstnew_export(char *str)
{
	t_envp *export;
	int i;

	i = 0;
	export = (t_envp *)malloc(sizeof(t_envp));
	if (!export)
		return (NULL);
	if (ft_isalpha(str))
	{
		export->var = ft_strdup(str);
		export->val = NULL;
	}
	else
	{
		export->var = ft_get_var_or_val_envp(str, 0);
		export->val = ft_get_var_or_val_envp(str, 1);
	}
	export->next = NULL;
	return (export);
}

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

static int ft_lstsize_env(t_envp *lst)
{
	int i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

static t_envp *ft_get_min_value(t_envp *export_list)
{
	t_envp *min;
	t_envp *tmp;
	int size;
	int i;

	i = 0;
	min = NULL;
	size = ft_lstsize_env(export_list);
	tmp = export_list;
	while (i < size - 1 && tmp->next != NULL)
	{
		if (ft_strcmp(tmp->var, tmp->next->var) >= 0)
		{
			tmp = tmp->next;
			i++;
			;
			continue;
		}
		if (min == NULL || ft_strcmp(min->var, tmp->var) > 0)
			min = tmp;
		tmp = tmp->next;
		i++;
	}
	return (min);
}

static void ft_print_sorted_envp_list(t_envp *export_list)
{
	t_envp *tmp;

	tmp = ft_get_min_value(export_list);
	while (tmp != NULL)
	{
		if (tmp->var != NULL && tmp->val != NULL)
			printf("declare -x %s=\"%s\"\n", tmp->var, tmp->val);
		else
			printf("declare -x %s\n", tmp->var);
		tmp = tmp->next;
	}
}

int ft_export(t_list *elem, t_var *var)
{
	int i;

	i = 1;
	if (elem->cmds[1] == NULL)
		ft_print_sorted_envp_list(var->export);
	else
	{
		while (elem->cmds[i] != NULL)
		{
			if (ft_strchr(elem->cmds[i], '=') && (ft_strlen(elem->cmds[i]) != 1))
			{
				ft_lstadd_back_envp(&var->envp, ft_lstnew_env(elem->cmds[i]));
				ft_lstadd_back_envp(&var->export, ft_lstnew_export(elem->cmds[i]));
			}
			else if (ft_isalpha(elem->cmds[i]))
				ft_lstadd_back_envp(&var->export, ft_lstnew_export(elem->cmds[i]));
			else if ((ft_isdigit(elem->cmds[i]) || ft_isprint(elem->cmds[i])))
			{
				ft_putstr_fd("minishelchik: export: `", STDERR_FILENO);
				ft_putstr_fd(elem->cmds[i], STDERR_FILENO);
				ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			}
			i++;
		}
	}
	return (0);
}

void ft_lstdelone_envp(t_var *var, t_list *elem, int j, int	index)
{
	t_envp	*tmp;
	t_envp	*begin;
	t_envp	*del;
	int		i;

	i = 1;
	if (j == 1)
		begin = var->envp;
	else
		begin = var->export;
	tmp = begin;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->var, elem->cmds[index]) == 0)
		{
			if (!tmp)
				return;
			if (begin == tmp)
				begin = tmp->next;
			else
			{
				del = begin;
				while (del && del->next != tmp)
					del = del->next;
				if (del)
					del->next = tmp->next;
			}
			if (tmp->var)
				free(tmp->var);
			if (tmp->val)
				free(tmp->val);
			free(tmp);
			continue ;
		}
		tmp = tmp->next;
	}
}

int ft_unset(t_var *var, t_list *elem)
{
	t_envp *tmp;
	int i;

	i = 1;
	while (elem->cmds[i] != NULL)
	{
		if (ft_isalpha(elem->cmds[i]))
		{
			ft_lstdelone_envp(var, elem, 0, i);
			ft_lstdelone_envp(var, elem, 1, i);
		}
		else
		{
			ft_putstr_fd("minishelchik: bash: `", STDERR_FILENO);
			ft_putstr_fd(elem->cmds[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int ft_env(t_list *elem, t_var *var)
{
	t_envp *tmp;

	tmp = var->envp;
	if (elem->cmds[1])
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(elem->cmds[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	while (tmp)
	{
		ft_putstr_fd(tmp->var, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(tmp->val, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int ft_exit(t_list *elem)
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