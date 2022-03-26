
#include "../minishell.h"

char	*check_result(char *result, int index)
{
	if (result)
		result[index] = 0;
	else
		result = ft_strdup("\0");
	return (result);
}

void	ft_skip_quotes(char **str)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ++(*str);
	while (temp[i] && (temp[i] != '\'' && temp[i] != '\"'))
		i++;
	*str = temp + i + 1;
}

void	ft_skip_redirect(char **str)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ++(*str);
	if (temp[i] && (temp[i] == '>' || temp[i] == '<'))
		i++;
	while (temp[i] && (temp[i] == ' ' || temp[i] == '\t'))
		i++;
	while (temp[i] && temp[i] != ' ' && temp[i] != '|')
		i++;
	*str = temp + i;
}

int	ft_limiter(char c)
{
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 62) \
		|| (c >= 91 && c <= 95) || (c >= 124 && c <= 126) \
		|| c == 64 || c == ' ')
		return (1);
	else
		return (0);
}

void	ft_free(char **dst)
{
	size_t	i;

	i = 0;
	while (dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
}
