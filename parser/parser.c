#include "../minishell.h"

void	*ft_realloc(char *result, int size)
{
	char	*temp;

	temp = result;
	if (result != NULL)
	{
		size += ft_strlen(result);
		result = (char *)ft_calloc(1, (size_t)size);
		ft_strlcpy(result, temp, size);
		//free(temp);
	}
	else
		result = (char *)ft_calloc(1, (size_t)size);
	return (result);
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
	while (**str)
	{
		i = 1;
		result = ft_realloc(result, i + 1);
		result[index++] = *(*str)++;
	}
	write(1, "ok\n", 3);
	if (result)
		result[index] = 0;
	else
		result = ft_strdup("\0");
	return (result);
}

int	add_in_cmds(char **result, char *temp, int shift)
{
	int		length;

	length = ft_strlen(temp);
	*result = ft_realloc(*result, length + 1);
	ft_strlcpy(*result + shift, temp, length + 1);
	free(temp);
	return (length);
}

char	*ft_parse_arguments(char **str, t_list *arguments)
{
	char	*temp;
	char	*result;
	int		shift;

	shift = 0;
	while (**str != ' ' && **str)
	{
//		if (**str == '\'')
//			temp = ft_parse_single_quote(str);
//		else if (**str == '\"')
//			temp = ft_parse_double_quote(str);
//		write(1, "ok\n", 3);
		if (**str == '|')
			temp = ft_parse_pipe(str, arguments);
		else if (**str == '>' || **str == '<')
			temp = ft_parse_redirect(str, arguments);
		else
			temp = ft_single_parse(str);
		if (temp)
			shift += add_in_cmds(&result, temp, shift);
	}
	if (result)
		result[shift] = 0;
	return (result);
}

void	ft_parser(char *str, t_list *arguments)
{
	t_list		*elem;
	char		*argument;
	char		*tmp;
	int			i;

	argument = NULL;
	i = 0;
	//printf("v%s\n", str);
	while (*str)
	{
		str += ft_skip_space(str);
        // write (1, "z\n", 2);
        //printf("a%s\n", str);
		arguments = NULL;
		//write (1, "z\n", 2);
		ft_lstadd_back(&arguments, ft_lstnew());
		//write (1, "2\n", 2);
		arguments->cmd = ft_parse_arguments(&str, arguments);
		printf("cmd: %s\n", arguments->cmd);
	}
}