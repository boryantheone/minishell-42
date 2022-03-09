
#include "../minishell.h"

int	g_status = 0;

void ft_error(void)
{
	printf("error\n");
}

void ft_printlist(t_list *elem)
{
	while(elem->next)
	{
		printf("cmd %s\ncmds %s\npath %s\n", elem->cmd, elem->cmds[1],
			   elem->path);
		elem = elem->next;
	}
	printf("cmd %s\ncmds %s\npath %s\n", elem->cmd, elem->cmds[1], elem->path);
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
		tmp->val =  new->val;
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
	while(elem->next)
	{
		if (elem->val && elem->var)
			printf("%s=%s\n", elem->var, elem->val);
		else
			printf("%s=%s\n", elem->var, elem->val);
		elem = elem->next;
	}
	printf("%s=%s\n", elem->var, elem->val);
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

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_var	*var;
	t_list	*elem;
	t_list	*elem2;
	t_list	*elem3;
	
	var = (t_var *)malloc(sizeof(t_var));
	var->envp = NULL;
	var->export = NULL;
	ft_make_env_list(env, var);
	var->export = (t_envp *)malloc(sizeof(t_envp *));
	var->export = var->envp;
	elem = ft_lstnew();
	elem = NULL;
	ft_lstadd_back(&elem, ft_lstnew());
	elem->cmd = "unset";
	elem->cmds = malloc(sizeof(char **) * 5);
	elem->cmds[0] = "unset";
	elem->cmds[1] = "SHLVL";
	elem->cmds[2] = "989";
	elem->cmds[3] = NULL;
	elem->path = "/usr/bin/export";
	elem->fd_in = -1;
	elem->fd_out = -1;
	// elem->cmd = "env";
	// elem->cmds = malloc(sizeof(char **) * 2);
	// elem->cmds[0] = "env";   
	//elem->cmds[1] = "/Users/boryantheone/Desktop/java projects\0";
	//elem->cmds[1] = " ";
	// elem->path = "/usr/bin/env";
	// elem->fd_in = -1;
	// elem->fd_out = -1;
	// elem->have_pipe = 0;
	// elem->cmd = "echo";
	// elem->cmds = malloc(sizeof(char **) * 4);
	// elem->cmds[0] = "echo";
	// elem->cmds[1] = "-n";
	// elem->cmds[2] = "123";
	// elem->cmds[3] = "123\0";
	//elem->cmds[1] = "/Users/boryantheone/Desktop/";
	//elem->cmds[2] = "123";
	// elem->path = "/bin/echo";
	// elem->fd_in = -1;
	// elem->fd_out = -1;
	// elem->have_pipe = 0;
	// ft_lstadd_back(&elem, ft_lstnew());
	// elem2 = elem->next;
	// elem2->cmd = "env";
	// elem2->cmds = malloc(sizeof(char **) * 3);
	// elem2->cmds[0] = "env";
	// elem2->path = "/usr/bin/env";
	// elem2->fd_in = -1;
	// elem2->fd_out = -1;
	// elem2->have_pipe = 0;
	// ft_lstadd_back(&elem, ft_lstnew());
	// elem3 = elem2->next;
	// elem3->cmd = "cat";
	// elem3->cmds = malloc(sizeof(char **) * 2);
	// elem3->cmds[0] = "cat";
	// elem3->cmds[1] = "-e";
	// elem3->path = "/bin/cat";
	// elem3->fd_in = -1;
	// elem3->fd_out = -1;
	// elem3->have_pipe = 0;
	//var->envp_for_execve = env;
	// ft_printlist(elem);
	while (1)
	{
		str = readline("minishelchik-1.0$ ");
		if (ft_strncmp(str, "\0", 1) != 0)
			add_history (str);
		if (!ft_preparser(str))
		{
			write (1, ")\n", 2);
			ft_parser(str, elem);
			//		ft_exec_pipes(var, elem);
		}
		//ft_exec_cmd(elem, var);
		//ft_exec_pipes(var, elem);
		//free(str);
		//rl_on_new_line();
	}
	return (0);
}