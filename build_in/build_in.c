#include "../minishell.h"

int ft_display_error(char *cmd, char *str)
{
	var->state = 127;
	ft_putstr_fd("minishelchik: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	if(!(ft_strcmp(cmd, "cd")))
	{
		var->state = 1;
		ft_putstr_fd(": ", 2);
		perror(NULL);
	}
	else
		ft_putstr_fd("\n", 2);
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

int	ft_cd_change_pwd(char *new_pwd, char *prev_pwd, t_envp **env)
{
	t_envp	*tmp;
	char	pwd[MAXDIR];

	tmp = *env;
	while (tmp)
	{
		if ((!ft_strncmp(tmp->var, "PWD", 3)))
		{
			getcwd(pwd, MAXDIR);
			if (!(ft_strcmp(new_pwd, "..")))
				tmp->val = pwd;
			else
				tmp->val = new_pwd;
		}
		tmp = tmp->next;
	}
	ft_cd_change_oldpwd(env, prev_pwd);
	free(tmp);
	return (EXIT_FAILURE);
}

int ft_cd(t_list *elem, t_var *var)
{
	char prev_pwd[MAXDIR];

	getcwd(prev_pwd, MAXDIR);
	if (elem->cmds[1] == NULL || !(ft_strncmp(elem->cmds[1], "~", 1)))
	{
		chdir(getenv("HOME"));
		return (EXIT_SUCCESS);
	}
	if (chdir(elem->cmds[1]) == -1)
	{
		write(1, "error\n", 6);
		return (ft_display_error("cd", elem->cmds[1]));
	}
	else
		ft_cd_change_pwd(elem->cmds[1], prev_pwd, &var->envp);
	var->state = 0;
	return (EXIT_SUCCESS);
}

static t_envp *ft_lstnew_export(char *str)
{
	t_envp *export;

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

static t_envp *ft_get_min_value(t_envp *pred_min)
{
	t_envp *min;
	t_envp *tmp;

	min = NULL;
	tmp = var->export;
	while (tmp != NULL)
	{
		if (pred_min != NULL && ft_strcmp(pred_min->var, tmp->var) >= 0)
		{
			tmp = tmp->next;
			continue ;
		}
		if (min == NULL || ft_strcmp(min->var, tmp->var) > 0)
			min = tmp;
		tmp = tmp->next;
	}
	return (min);
}

static void ft_print_sorted_envp_list(void)
{
	t_envp *tmp;

	tmp = ft_get_min_value(NULL);
	while (tmp != NULL)
	{
		if (tmp->var != NULL && tmp->val != NULL)
			printf("declare -x %s=\"%s\"\n", tmp->var, tmp->val);
		else
			printf("declare -x %s\n", tmp->var);
		tmp = ft_get_min_value(tmp);
	}
}

int ft_export(t_list *elem, t_var *var)
{
	int i;

	i = 1;
	var->state = 0;
	if (elem->cmds[1] == NULL)
		ft_print_sorted_envp_list();
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
				ft_lstadd_back_envp(&var->export, ft_lstnew_export
				(elem->cmds[i]));
			else if ((ft_isdigit(elem->cmds[i]) || ft_isprint(elem->cmds[i])))
			{
				var->state = 1;
				ft_putstr_fd("minishelchik: export: `", STDERR_FILENO);
				ft_putstr_fd(elem->cmds[i], STDERR_FILENO);
				ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			}
			i++;
		}
	}
	return (0);
}

