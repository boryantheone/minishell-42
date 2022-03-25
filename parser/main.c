
#include "../minishell.h"

static void	ft_init_var(char **env)
{
	g_var = (t_var *)malloc(sizeof(t_var));
	g_var->state = 0;
	g_var->envp = NULL;
	g_var->export = NULL;
	ft_make_env_list(env);
	g_var->export = g_var->envp;
}

static int	ft_minishell(char *str)
{
	t_list	*elem;
	t_fds	*fds;

	if (!ft_preparser(str))
	{
		fds = ft_parser_heredoc(str);
		if (fds == NULL && g_var->state == 258)
			return (1);
		ft_parser_redirect(str, fds);
		elem = ft_parser(str);
		ft_execute(elem, fds);
		ft_lstclear_fds(&fds);
		ft_lstclear(&elem);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;

	ft_init_var(env);
	while (1)
	{
//		rl_catch_signals = 0;
		ft_init_signal_handler(ft_handler_main);
		str = readline("\033[1;35mminishelchik-1.0$ \033[0m");
		if (str == NULL)
			ft_handler_ctrl_d();
		if (ft_strncmp(str, "\0", 1) != 0)
			add_history (str);
		else
		{
			free(str);
			continue;
		}
		if (str != NULL)
		{
			ft_minishell(str);
		}
		free(str);
	}
}