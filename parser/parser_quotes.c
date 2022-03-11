#include "../minishell.h"

static char	*ft_strndup(const char *src, int len)
{
	char	*result;
	size_t	i;
	size_t 	str_len;
	
	i = 0;
	str_len = ft_strlen(src);
	if (len > str_len)
		len = str_len;
	if (!(result = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*src && len--)
		result[i++] = *(src++);
	result[i] = '\0';
	return (result);
}

char *ft_parse_single_quote(char **str)
{
	int		index;
	char	*temp;
	char	*result;
	
	temp = ++(*str);
	index = 0;
	while (temp[index] && temp[index] != '\'')
		index++;
	if (index)
		result = ft_strndup(temp, index);
	else
		result = ft_strdup("\0");
	if (*temp == '\'')
		temp++;
	*str = temp;
	return (result);
}

char *ft_parse_double_quote(char **str)
{
	int		index;
	char	*temp;
	char	*result;
	
	temp = ++(*str);
	index = 0;
	// while (temp[index] && temp[index] != '\"')
	// {
	// 	temp = NULL;
	// 	if (**str == '$')
	// 		temp = parse_with_envp()
	// 	index++;
	// }
}
