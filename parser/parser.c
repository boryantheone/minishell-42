#include "../minishell.h"

char	*ft_single_parse(char **str)
{
	char	*result;
	char	*temp;
	int		i;
	int		index;

	index = 0;
	result = NULL;
	while (**str != ' ' && **str != '\0' && **str != '|' \
	&& **str != '\"' && **str != '\'')
	{
		temp = NULL;
		if (**str == '$')
			temp = ft_parse_with_envp(str, 0);
		if (temp)
			i = (int)ft_strlen(temp);
		else
			i = 1;
		result = ft_realloc(result, i + 1);
		if (temp)
			index += ft_add_in_result(result, temp, i, index);
		else
			result[index++] = *(*str)++;
	}
	result = check_result(result, index);
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
	if (result)
		result[shift] = '\0';
	return (result);
}

t_list	*ft_help_parser(char *str, t_list *elem, char **arguments, char *tmp)
{
	int	i;

	i = 0;
	while (*str)
	{
		while (*str == ' ')
			str++;
		if (*str == '|')
		{
			ft_lstadd_back(&elem, ft_lstnew(arguments));
			arguments = NULL;
			i = 0;
			str++;
		}
		if (*str == '>' || *str == '<')
			ft_skip_redirect(&str);
		if ((tmp = ft_parse_arguments(&str)))
		{
			arguments = ft_double_realloc(arguments, 1);
			arguments[i++] = tmp;
		}
	}
	if (*str == '\0')
		ft_lstadd_back(&elem, ft_lstnew(arguments));
	return (elem);
}

t_list	*ft_parser(char *str)
{
	char		**arguments;
	char		*tmp;
	t_list		*elem;

	arguments = NULL;
	elem = NULL;
	tmp = NULL;
	elem = ft_help_parser(str, elem, arguments, tmp);
	printf("end of parser\n");
	return (elem);
}