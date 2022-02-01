
#include "../minishell.h"

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
	t_list	*elem2;
	
	(void)argc;
	(void)argv;
	
	var = (t_var *)malloc(sizeof(t_var));
	var->elem = NULL;
	ft_lstadd_back(&var->elem, ft_lstnew());
	var->elem->cmd = "ls";
	var->elem->cmds = "ls -l";
	var->elem->path = "/bin/ls";
	ft_lstadd_back(&var->elem, ft_lstnew());
	elem2 = var->elem->next;
	elem2->cmd = "pwd";
	elem2->cmds = "wc";
	elem2->path = "/bin/pwd";
	ft_printlist(var->elem);
	while (1)
	{
		str = readline("Myshell $ ");
		ft_preparser(str);
		ft_parser(str, env);
		ft_load_cmds(var);
		free(str);
	}
	return (0);
}