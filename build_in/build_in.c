
#include "../minishell.h"

int	ft_display_error(char *cmd, char *str)
{
	g_var->state = 127;
	ft_putstr_fd("minishelchik: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	if (!(ft_strcmp(cmd, "cd")))
	{
		g_var->state = 1;
		ft_putstr_fd(": ", 2);
		perror(NULL);
	}
	if (!(ft_strcmp(cmd, "export")))
	{
		g_var->state = 1;
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else
		ft_putstr_fd("\n", 2);
	return (EXIT_FAILURE);
}

static t_envp	*ft_lstnew_export(char *str)
{
	t_envp	*export;

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

static t_envp	*ft_get_min_value(t_envp *pred_min)
{
	t_envp	*min;
	t_envp	*tmp;

	min = NULL;
	tmp = g_var->export;
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

static void	ft_print_sorted_envp_list(void)
{
	t_envp	*tmp;

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

int	ft_export(t_list *elem)
{
	int	i;

	i = 1;
	g_var->state = 0;
	if (elem->cmds[1] == NULL)
		ft_print_sorted_envp_list();
	else
	{
		while (elem->cmds[i] != NULL)
		{
			if (ft_strchr(elem->cmds[i], '=') && (ft_strlen(elem->cmds[i]) != 1))
			{
				ft_lstadd_back_envp(&g_var->envp, ft_lstnew_env(elem->cmds[i]));
				ft_lstadd_back_envp(&g_var->export, ft_lstnew_export(elem->cmds[i]));
			}
			else if (ft_isalpha(elem->cmds[i]))
				ft_lstadd_back_envp(&g_var->export, ft_lstnew_export(elem->cmds[i]));
			else if ((ft_isdigit(elem->cmds[i]) || ft_isprint(elem->cmds[i])))
				ft_display_error("export", elem->cmds[i]);
			i++;
		}
	}
	return (0);
}
