
#include "../minishell.h"

int	ft_preparser_quotes(const char *line, int *i, int man)
{
	(*i)++;
	while (line[(*i)] && line[(*i)] != man)
		(*i)++;
	if (!line[(*i)] || line[(*i)] != man)
	{
		g_var->state = 258;
		if (man == 39)
			printf("minishelchik: syntax error near unexpected token `\''\n");
		if (man == 34)
			printf("minishelchik: syntax error near unexpected token `\"'\n");
		return (1);
	}
	return (0);
}

static int	ft_preparser_reverse_redirect(char *line, int *i)
{
	if (line[(*i)] == '<')
	{
		(*i)++;
		if (!(ft_skip_space(line, i)))
			return (ft_write_error(2));
		if (line[(*i)] == '>')
			return (ft_write_error(1));
		if (line[(*i)] == '<' && line[(*i) + 1] && \
		(line[(*i) + 1] == '<' || line[(*i) + 1] == '>'))
			return (ft_write_error(1));
//		(*i)++;
//		if (!(ft_skip_space(line, i)))
//			return (ft_write_error(2));
	}
	return (0);
}

int	ft_preparser_redirect(char *line, int *i)
{
	if (line[(*i)] == '<')
		if ((ft_preparser_reverse_redirect(line, i)))
			return (1);
	if (line[(*i)] == '>')
	{
		(*i)++;
		if (!(ft_skip_space(line, i)))
			return (ft_write_error(2));
		if (line[(*i)] == '<')
			return (ft_write_error(3));
		if (line[(*i)] == '>' && line[(*i) + 1] && \
		(line[(*i) + 1] == '<' || line[(*i) + 1] == '>'))
			return (ft_write_error(3));
//		(*i)++;
//		if (!(ft_skip_space(line, i)))
//			return (ft_write_error(2));
	}
	return (0);
}

int	ft_preparser_pipe(const char *line, int *i)
{
	if (line[(*i)] == 124)
	{
		(*i)++;
		while (line[(*i)] && line[(*i)] == ' ' && line[(*i)] != 34 && \
		line[(*i)] != 39)
			(*i)++;
		if (line[(*i)] == '\0' || line[(*i)] == 124)
		{
			g_var->state = 258;
			printf("minishelchik: syntax error unexpected token `|'\n");
			return (1);
		}
	}
	return (0);
}

int	ft_preparser(char *line)
{
	int	i;

	i = 0;
	if (!(ft_skip_space(line, &i)))
		return (1);
	while (line[i])
	{
		if (line[i] == 124)
			if (ft_preparser_pipe(line, &i))
				return (1);
		if (line[i] == 34)
			if (ft_preparser_quotes(line, &i, 34))
				return (1);
		if (line[i] == 39)
			if (ft_preparser_quotes(line, &i, 39))
				return (1);
		if (ft_preparser_redirect(line, &i))
			return (1);
		i++;
	}
	return (0);
}
