
#include "../minishell.h"

char	*ft_strndup(char *src, int len)
{
	char	*result;
	int		i;
	int		str_len;

	i = 0;
	str_len = (int)ft_strlen(src);
	if (len > str_len)
		len = str_len;
	if (!(result = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*src && len--)
		result[i++] = *(src++);
	result[i] = '\0';
	return (result);
}

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

char *ft_parse_double_quote(char **str)
{
	int		index;
	char	*temp;
	char	*result;
	int		i;

	++(*str);
	index = 0;
	result = NULL;
//	printf("%s\n", result);
	while (**str && **str != '\"')
	{
		temp = NULL;
		if (**str == '$')
		{
//			write(1,"@\n",2);
			temp = ft_parse_with_envp(str, 0);
//			printf("$ temp %s\n", temp);
		}
		i = (temp) ? ft_strlen(temp) : 1;
//		printf("str quote %s\n", *str);
		result = ft_realloc(result, i + 1);
		if (temp)
			index += ft_add_in_result(result, temp, i, index);
		else
			result[index++] = *(*str)++;
	}
	if (**str == '\"')
		(*str)++;
	if (result)
		result[index] = 0;
	else
		result = ft_strdup("\0");
	return (result);
}
