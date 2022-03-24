
#include "../minishell.h"

char	*ft_get_var_or_val_envp(char *str, int or)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (or == 0)
	{
		tmp = (char *)malloc((sizeof(char *) * i) + 2);
		i = -1;
		while (str[++i] != '=')
			tmp[i] = str[i];
		tmp[i] = '\0';
	}
	else
	{
		tmp = (char *)malloc((sizeof(char *) * (ft_strlen(str) - i)) + 1);
		j = 0;
		while (str[++i])
			tmp[j++] = str[i];
		tmp[j] = '\0';
	}
	return (tmp);
}

t_envp	*ft_lstnew_env(char *str)
{
	t_envp	*env;

	env = (t_envp *)malloc(sizeof(t_envp));
	if (!env)
		return (NULL);
	env->var = ft_get_var_or_val_envp(str, 0);
	if (!ft_strncmp(str, "SHLVL", 5))
		env->val = ft_itoa(ft_atoi(ft_get_var_or_val_envp(str, 1)) + 1);
	else if (!ft_strncmp(str, "_", 1))
		env->val = ft_strdup("/usr/bin/env");
	else
		env->val = ft_get_var_or_val_envp(str, 1);
	env->next = NULL;
	return (env);
}

void	ft_lstadd_back_envp(t_envp **lst, t_envp *new)
{
	t_envp	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
	{
		if (!(ft_strcmp(tmp->var, new->var)))
		{
			tmp->val =  new->val;
			return ;
		}
		tmp = tmp->next;
	}
	if (!(ft_strcmp(tmp->var, new->var)))
	{
		tmp->val = new->val;
		return ;
	}
	tmp -> next = new;
}

int	ft_make_env_list(char **env)
{
	int	i;

	if (!env)
		return (EXIT_FAILURE);
	i = -1;
	while (env[++i])
		ft_lstadd_back_envp(&g_var->envp, ft_lstnew_env(env[i]));
	return (EXIT_SUCCESS);
}