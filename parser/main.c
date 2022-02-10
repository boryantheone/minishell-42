
#include "../minishell.h"

int	g_status = 0;

void ft_error(void)
{
	printf("error\n");
}

int		ft_skip_space(char *line)
{
	int		i;
	
	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

int ft_preparser(char *line)
{
	int	i;
	int	flag;
	
	flag = 0;
	i = ft_skip_space(line);
	if (line[i] == 124)
		ft_error();
//	while (line[i])
//	{
//		if (line[i] == 34 || line[i] == 39)
//			flag++;
//		i++;
//	}
	if (line[i] == 34 || line[i] == 39)
	{
		i++;
		while (line[i] && line[i] != 34 && line[i] != 39)
			i++;
		if (!line[i])
		{
			ft_error();
			return (1);
		}
	}
	return (0);
}

char	*ft_quote_marks(char *line, int *i)
{
	int	j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;
	
	while (line[++(*i)])
		if (line[*i] == 39)
			break ;
	tmp = ft_substr(line, 0, j);
	printf("tmp %s\n", tmp);
	tmp2 = ft_substr(line, j + 1, *i - j - 1);
	printf("tmp2 %s\n", tmp2);
	tmp3 = ft_strdup(line + *i + 1);
	printf("tmp3 %s\n", tmp3);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	printf("tmp000 %s\n", tmp);
	free(tmp2);
	free(tmp3);
	return (tmp);
}

void ft_parser(char *line, char **env)
{
	int	i;
	
	i = -1;
	while (line[++i])
	{
		if (line[i] == 39)
			line = ft_quote_marks(line, &i);
	//	printf("%s\n", line);
	}
	//printf("%s\n", line);
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
	// elem->cmd = "cd";
	// elem->cmds = malloc(sizeof(char **) * 2);
	// elem->cmds[0] = "cd";   
	// elem->cmds[1] = "/Users/jcollin/Desktop/GNL";   
	// elem->path = "/usr/bin/cd";
	// elem->fd_in = -1;
	// elem->fd_out = -1;
	elem->cmd = "ls";
	elem->cmds = malloc(sizeof(char **) * 3);
	elem->cmds[0] = "ls";   
	elem->cmds[1] = "-l";   
	elem->path = "/bin/ls";
	elem->fd_in = -1;
	elem->fd_out = -1;
	elem->have_pipe = 0;
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
	ft_lstadd_back(&elem, ft_lstnew());
	elem2 = elem->next;
	elem2->cmd = "wc";
	elem2->cmds = malloc(sizeof(char **) * 3);
	elem2->cmds[0] = "wc";
	elem2->cmds[1] = "-l";
	elem2->path = "/usr/bin/wc";
	elem2->fd_in = -1;
	elem2->fd_out = -1;
	elem2->have_pipe = 0;
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
	ft_printlist(elem);
	var->envp = env;
	while (1)
	{
		str = readline("Myshell $ ");
		ft_preparser(str);
		ft_parser(str, env);
		//ft_exec_cmd(elem, var);
		ft_exec_pipes(var, elem);
		free(str);
		//rl_on_new_line();
	}
	return (0);
}