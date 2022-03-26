
#include "../minishell.h"

char	*ft_parse_single_quote(char **str)
{
	int		index;
	char	*temp;
	char	*result;

	temp = ++(*str);
	index = 0;
	while (temp[index] && (temp[index] != '\''))
		index++;
	if (index)
		result = ft_strndup(temp, index);
	else
		result = ft_strdup("\0");
	if (*(temp + index) == '\'')
		temp += index + 1;
	*str = temp;
	return (result);
}

int	ft_add_in_result(char *result, char *temp, int i, int index)
{
	ft_strcpy(result + index, temp);
	free(temp);
	return (i);
}

static int	ft_i(char *temp)
{
	int		i;

	if (temp)
		i = (int)ft_strlen(temp);
	else
		i = 1;
	return (i);
}

char	*ft_parse_double_quote(char **str)
{
	int		index;
	char	*temp;
	char	*result;
	int		i;

	++(*str);
	index = 0;
	result = NULL;
	while (**str && **str != '\"')
	{
		temp = NULL;
		if (**str == '$')
			temp = ft_parse_with_envp(str, 0);
		i = ft_i(temp);
		result = ft_realloc(result, i + 1);
		if (temp)
			index += ft_add_in_result(result, temp, i, index);
		else
			result[index++] = *(*str)++;
	}
	if (**str == '\"')
		(*str)++;
	result = check_result(result, index);
	return (result);
}
