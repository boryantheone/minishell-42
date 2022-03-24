
#include "../minishell.h"

void ft_printlist(t_list *elem)
{
	t_list *tmp;
	
	tmp = elem;
//	write(2, "++++++++++++++++++++++++\n", 26);
	if(tmp)
	{
		while (tmp != NULL)
		{
			printf("cmds %s|", tmp->cmds[0]);
			tmp = tmp->next;
		}
	}
	else
		printf("elem not found\n");
	printf("\n----------------------\n");
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
}

int	ft_check_fds(t_fds *fds)
{
	t_fds	*tmp_fds;

	tmp_fds = fds;
	if (tmp_fds != NULL)
	{
		if (tmp_fds->fd_in == -1 || tmp_fds->fd_out == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	eof_e(void)
{
	write(1, "exit\n", 5);
	return (g_var->state);
}

void	ft_init_var(char **env)
{
	g_var = (t_var *)malloc(sizeof(t_var));
	g_var->state = 0;
	g_var->envp = NULL;
	g_var->export = NULL;
	ft_make_env_list(env);
	g_var->export = (t_envp *)malloc(sizeof(t_envp *));
	g_var->export = g_var->envp;
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_list	*elem;
	t_fds	*fds;

	ft_init_var(env);
	while (1)
	{
		rl_catch_signals = 0;
		ft_init_signal_handler(ft_handler_main);
		str = readline("\033[1;35mminishelchik-1.0$ \033[0m");
		if (str == NULL)
			ft_handler_ctrl_d();
		if (ft_strncmp(str, "\0", 1) != 0)
			add_history (str);
		else
			continue;
		if (!ft_preparser(str))
		{
			fds = ft_parser_heredoc(str);
			if (fds == NULL && g_var->state == 258)
				continue;
			ft_parser_redirect(str, fds);
			elem = ft_parser(str);
			ft_execute(elem, fds);
//			free(fds);
//			ft_lstclear(&elem);
		}
		free(str);
	}
}