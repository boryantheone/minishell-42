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

char	*ft_parse_redirect(char **str, t_list *arguments)
{
	(void *)str;
	(void *)arguments;
}

char	*ft_parse_pipe(char **str, t_list *arguments)
{
	(void *)str;
	(void *)arguments;
}

char	*ft_single_parse(char **str)
{
	char	*result;
	int		i;
	int		index;

	index = 0;
	result = NULL;
	while (**str != ' ' && **str != '\0')
	{
		i = 1;
		result = ft_realloc(result, i + 1);
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

	length = ft_strlen(temp);
//	write(1, "add in cmds\n", 12);
//	printf("shift %d\n", shift);
//	printf("result %s\n", *result);
	*result = ft_realloc(*result, length + 1);
	ft_strcpy(*result + shift, temp);
	//write(1, "add in cmds\n", 12);
	free(temp);
	return (length);
}

char	*ft_parse_arguments(char **str, t_list *arguments)
{
	char	*temp;
	char	*result;
	int		shift;

	shift = 0;
	result = NULL;
	while (**str)
	{
		if (**str == ' ')
			break ;
		// if (**str == '\'')
		// 	temp = ft_parse_single_quote(str);
		// else if (**str == '\"')
		// 	temp = ft_parse_double_quote(str);
		else if (**str == '|')
			temp = ft_parse_pipe(str, arguments);
  		else if (**str == '>' || **str == '<')
   			temp = ft_parse_redirect(str, arguments);
		else
			temp = ft_single_parse(str);
		if (temp)
			shift += add_in_cmds(&result, temp, shift);
	}
	//printf("res %s\n", result);
	if (result)
		result[shift] = '\0';
	return (result);
//	arguments->cmd = result;
//	printf("cmd: %s\n", arguments->cmd);
//	if (**str == '-' && *(*str + 1) != '-')
}

void	*ft_parser(char *str, t_list *elem)
{
	char		**arguments;
	t_list 		*r;
	t_list		*begin;
	char		*tmp;
	int			i;
	
	i = 0;
//	begin = NULL;
	arguments = NULL;
	str += ft_skip_space(str);
	while (*str)
	{
        // write (1, "z\n", 2);
        //printf("a %s\n", str);
		while (*str == ' ')
			str++;
		if (*str == '|')
		{
			//r = ft_lstnew(arguments);
			ft_lstadd_back(&elem, ft_lstnew(arguments));
			printf("have pipe\n");
			arguments = NULL;
			ft_printlist(elem);
//			if (arguments != NULL)
//				ft_malloc_free(arguments);
			i = 0;
			str++;
		}
		if ((tmp = ft_parse_arguments(&str, elem)))
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
		//r = ft_lstnew(arguments);
		ft_lstadd_back(&elem, ft_lstnew(arguments));
	}
	ft_printlist(elem);
	printf("end of parser\n");

}