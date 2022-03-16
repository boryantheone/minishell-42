#include "../minishell.h"

char	*ft_strcpy(char *dest, char *src)
{
	while (*src != '\0')
		*dest++ = *src++;
	return (dest);
}

void	*ft_realloc(char *result, int size)
{
	char	*temp;

	temp = result;
	if (result != NULL)
	{
		size += ft_strlen(result);
		result = (char *)ft_calloc(1, (size_t)size);
		ft_strcpy(result, temp);
		free(temp);
	}
	else
		result = (char *)ft_calloc(1, (size_t)size);
	return (result);
}

int	ft_str_double_len(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

char	**ft_double_realloc(char **cmds, int size)
{
	char	**temp;
	int		i;

	i = 0;
	temp = cmds;
	if (cmds)
	{
		size += ft_str_double_len(cmds);
		cmds = (char **)malloc(sizeof(char *) * (size + 1));
		while (i < size)
		{
			cmds[i] = temp[i];
			i++;
		}
		cmds[i] = NULL;
		free(temp);
	}
	else
	{
		cmds = (char **)malloc(sizeof(char *) * (size + 1));
		cmds[size] = NULL;
	}
	return (cmds);
}

char	*ft_single_parse(char **str)
{
	char	*result;
	char	*temp;
	int		i;
	int		index;

	index = 0;
	result = NULL;
	while (**str != ' ' && **str != '\0' && **str != '|')
	{
		temp = NULL;
		if (**str == '$')
		{
			//write(1,"@\n",2);
			temp = ft_parse_with_envp(str, 0);
			printf("$ temp %s\n", temp);
		}
		if (temp)
			i = ft_strlen(temp);
		else
			i = 1;
		result = ft_realloc(result, i + 1);
		if (temp)
			index += ft_add_in_result(result, temp, i, index);
		else
			result[index++] = *(*str)++;
	}
	if (result)
		result[index] = '\0';
	else
		result = ft_strdup("\0");
	//printf("RESULT %s\n", result);
	return (result);
}

int	add_in_cmds(char **result, char *temp, int shift)
{
	int		length;

	length = (int)ft_strlen(temp);
	*result = ft_realloc(*result, length + 1);
	ft_strcpy(*result + shift, temp);
	free(temp);
	return (length);
}

char	*ft_parse_arguments(char **str)
{
	char	*temp;
	char	*result;
	int		shift;

	shift = 0;
	result = NULL;
	while (**str)
	{
		if (**str == ' ' || **str == '|')
			break ;
		if (**str == '\'')
			temp = ft_parse_single_quote(str);
		else if (**str == '\"')
			temp = ft_parse_double_quote(str);
		else
			temp = ft_single_parse(str);
		if (temp)
			shift += add_in_cmds(&result, temp, shift);
	}
	//printf("res %s\n", result);
	if (result)
		result[shift] = '\0';
	return (result);
}

t_list	*ft_parser(char *str)
{
	char		**arguments;
	char		*tmp;
	int			i;
	t_fds		*fds;
	t_list		*elem;
	t_list		*temp;

	i = 0;
	arguments = NULL;
	elem = NULL;
	temp = NULL;
//	printf("%s\n", str);
	while (*str)
	{
        // write (1, "z\n", 2);
		while (*str == ' ' || *str == '>' || *str == '<')
			str++;
		//printf("STR %s\n", str);
		if (*str == '|')
		{
			temp = ft_lstnew(arguments);
			ft_lstadd_back(&elem, temp);
			printf("have pipe\n");
			arguments = NULL;
			ft_printlist(elem);
			i = 0;
			str++;
		}
//		while (*str == '>' || *str == '<')
//			str++;
		if ((tmp = ft_parse_arguments(&str)))
		{
			//("TMP %s\n", tmp);
			arguments = ft_double_realloc(arguments, 1);
			arguments[i] = tmp;
			printf("CMDS % d %s\n", i, arguments[i]);
			i++;
		}
	}
	if (*str == '\0')
	{
		temp = ft_lstnew(arguments);
		ft_lstadd_back(&elem, temp);
	}
	ft_printlist(elem);
	printf("end of parser\n");
	return (elem);
}