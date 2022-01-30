
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

void ft_preparser(char *line)
{
	int i;
	
	i = ft_skip_space(line);
	if (line[i] == 124)
		ft_error();
	if (line[i] == 34 || line[i] == 39)
	{
		i++;
		while (line[i] && line[i] != 34 && line[i] != 39)
			i++;
		if (!line[i])
			ft_error();
	}
	
	
	
}

int	main(void)
{
	char	*str;
	
	while (1)
	{
		str = readline("Myshell $ ");
		ft_preparser(str);
        free(str);
	}
	
}