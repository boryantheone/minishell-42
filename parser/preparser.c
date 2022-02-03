
#include "../minishell.h"

int		ft_skip_space(char *line)
{
	int		i;
	
	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

int ft_preparser_quotes(char *line, int *i, int man)
{
	(*i)++;
	while (line[(*i)] && line[(*i)] != man)
		(*i)++;
	if (!line[(*i)] || line[(*i)] != man)
	{
		printf("Input error\n");
		return (1);
	}
	return (0);
}

int ft_preparser_redirect(char *line, int *i)
{
	if ((line[(*i)] == '<' && line[(*i) + 1] && line[(*i) + 1] == '>') || \
		(line[(*i)] == '>' && line[(*i) + 1] && line[(*i) + 1] == '<'))
	{
		printf("Input error: <>\n");
		return (1);
	}
	if ((line[(*i)] == '<' && line[(*i) + 1] && line[(*i) + 1] == '<' && line[(*i) + 2] && \
		line[(*i) + 2] == '<') || (line[(*i)] == '>' && line[(*i) + 1] && line[(*i) + 1] == '>' \
		&& line[(*i) + 2] && line[(*i) + 2] == '>'))
	{
		printf("Input error: <>\n");
		return (1);
	}
	
	return (0);
}
//124 = '|'
int	ft_preparser(char *line)
{
	int	i;
	
	i = ft_skip_space(line);
	if (line[i--] == 124)
	{
		printf("syntax error near unexpected token `|'\n");
		exit (1);
	}
	while (line[++i])
	{
		if (line[i] == 34)
			if (ft_preparser_quotes(line, &i, 34))
				return (1);
		if (line[i] == 39)
			if (ft_preparser_quotes(line, &i, 39))
				return (1);
		if (line[i] == 124 && line[i + 1] && line[i + 1] == 124)
		{
			printf("syntax error near unexpected token `|'\n");
			return (1);
		}
		if (ft_preparser_redirect(line, &i))
			return (1);
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

