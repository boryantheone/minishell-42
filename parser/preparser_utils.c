
#include "../minishell.h"

int	ft_skip_space(const char *line, int *i)
{
	if (line[(*i)] == 124)
	{
		g_var->state = 258;
		printf("minishelchik: syntax error near unexpected token `|'\n");
		return (0);
	}
	while (line[(*i)] == ' ')
		(*i)++;
	if (line[(*i)] == '\0')
		return (0);
	if (line[(*i)] == 124)
	{
		g_var->state = 258;
		printf("minishelchik: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

int	ft_write_error(int flag)
{
	g_var->state = 258;
	if (flag == 1)
		printf("minishelchik: syntax error near unexpected token `<'\n");
	if (flag == 2)
		printf("minishelchik: syntax error near unexpected token `newline'\n");
	if (flag == 3)
		printf("minishelchik: syntax error near unexpected token `>'\n");
	return (1);
}
