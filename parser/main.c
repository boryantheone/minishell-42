
#include "../minishell.h"

void ft_error(void)
{
	printf("error\n");
}

void ft_printlist(t_list *elem)
{
	t_list *tmp;
	
	tmp = elem;
//	write(2, "++++++++++++++++++++++++\n", 26);
	if(tmp)
	{
		while (tmp != NULL)
		{
			printf("cmds %s|", tmp->cmd);
			tmp = tmp->next;
		}
	}
	else
		printf("elem not found\n");
	printf("\n----------------------\n");
}

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
	t_envp *env;

	env = (t_envp *)malloc(sizeof(t_envp));
	if (!env)
		return (NULL);
	env->var = ft_get_var_or_val_envp(str, 0);
	if (!ft_strncmp(str, "SHLVL", 5))
		env->val = ft_itoa(ft_atoi(ft_get_var_or_val_envp(str, 1)) + 1);
	else if(!ft_strncmp(str, "_", 1))
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

int	ft_make_env_list(char **env, t_var  *var)
{
	int	i;

	if (!env)
		return (EXIT_FAILURE);
	i = -1;
	while (env[++i])
		ft_lstadd_back_envp(&var->envp, ft_lstnew_env(env[i]));
	return (EXIT_SUCCESS);

}

void ft_printlist_envp(t_envp *elem)
{
	while(elem != NULL)
	{
		if (elem->val && elem->var)
			printf("%s=%s\n", elem->var, elem->val);
		else
			printf("%s=%s\n", elem->var, elem->val);
		elem = elem->next;
	}
	//printf("%s=%s\n", elem->var, elem->val);
}

// void ft_printlist_envp(t_var *var)
// {
// 	while(var->envp->next)
// 	{
// 		printf("var %s val %s\n", var->envp->var, var->envp->val);
// 		var->envp = var->envp->next;
// 	}
// 	printf("var %s\nval %s\n", var->envp->var, var->envp->val);
// }

int	ft_check_fds(t_fds *fds)
{
	t_fds *tmp_fds;

	tmp_fds = fds;
	if (tmp_fds != NULL)
	{
		if (tmp_fds->fd_in == -1 || tmp_fds->fd_out == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	eof_exit(void)
{
	write(1, "exit\n", 5);
	return (var->state);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_list	*elem;
	t_fds	*fds;

	var = (t_var *)malloc(sizeof(t_var));
	var->envp = NULL;
	var->envp_for_execve = env;
	var->export = NULL;
	var->state = 0;
	ft_make_env_list(env, var);
	var->export = (t_envp *)malloc(sizeof(t_envp *));
	var->export = var->envp;
	while (1)
	{
		str = readline("minishelchik-1.0$ ");
		if (ft_strncmp(str, "\0", 1) != 0)
			add_history (str);
		if (str != NULL)
		{
			if (!ft_preparser(str))
			{
				fds = ft_parser_heredoc(str);
				if (fds == NULL && var->state == 258)
					continue;
				ft_parser_redirect(str, fds);
				elem = ft_parser(str);
				ft_printlist(elem);
				ft_execute(var, elem, fds);
			}
			free(str);
		}
		else
			return (eof_exit());
	}
	
	return (0);
}