
#include "../minishell.h"

int	g_status = 0;

void ft_error(void)
{
	printf("error\n");
}

void ft_parser(char *line, char **env)
{
	int	i;

	i = -1;
//	while (line[++i])
//	{
//		if (line[i] == 39)
////			line = ft_quote_marks(line, &i);
//	//	printf("%s\n", line);
//	}
	printf("%s\n", line);
}

void ft_printlist(t_list *elem)
{
	while(elem->next)
	{
		printf("cmd %s\ncmds %s\npath %s\n", elem->cmd, elem->cmds,
			   elem->path);
		elem = elem->next;
	}
	printf("cmd %s\ncmds %s\npath %s\n", elem->cmd, elem->cmds, elem->path);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_var	*var;
	t_list	*elem;
	t_list	*elem2;
	t_list	*elem3;
	
	(void)argc;
	(void)argv;
	
	var = (t_var *)malloc(sizeof(t_var));
	elem = ft_lstnew();
	elem = NULL;
	ft_lstadd_back(&elem, ft_lstnew());
	elem->cmd = "ls";
	elem->path = "/bin/ls";
	elem->fd_in = open("1.txt", O_RDWR);
	elem->cmds = "ls -l";   
	elem->path = "ls";
	elem->fd_in = open("/Users/jcollin/Desktop/GNL", O_RDWR);
	elem->fd_out = -1;
	elem->have_pipe = 0;
	ft_lstadd_back(&elem, ft_lstnew());
	elem3 = elem->next;
	elem3->cmd = "pwd";
	elem3->path = "/bin/pwd";
	//ft_printlist(var->elem);
	elem2 = elem->next;
	elem2->cmd = "wc";
	elem2->cmds = "wc -l";
	elem2->path = "/usr/bin/wc";
	elem2->fd_in = -1;
	elem2->fd_out = -1;
	elem2->have_pipe = 0;
	ft_lstadd_back(&elem, ft_lstnew());
	elem3 = elem2->next;
	elem3->cmd = "cat";
	elem3->cmds = "cat -e";
	elem3->path = "/bin/cat";
	elem3->fd_in = -1;
	elem3->fd_out = -1;
	elem3->have_pipe = 0;
	ft_printlist(elem);
	var->envp = env;
	while (1)
	{
		str = readline("Myshell $ ");
		if (ft_strncmp(str, "\0", 1) != 0)
			add_history (str);
		if (!ft_preparser(str))
		{
			ft_parser(str, env);
	//		ft_exec_pipes(var, elem);
		}
		ft_preparser(str);
		ft_parser(str, env);
		//ft_exec_cmd(elem, var);
		ft_exec_pipes(var, elem);
		free(str);
	}
	return (0);
}