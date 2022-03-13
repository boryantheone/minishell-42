#include "../minishell.h"

int	ft_double_redirect(char **temp)
{
	int		fd;
	char	*file_name;

	++(*temp);
	printf("temp %s\n", *temp);
	while ((**temp == ' ' || **temp == '\t') && **temp != '\0')
		(*temp)++;
	file_name = ft_parse_arguments(temp);
	fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	free(file_name);
	return (fd);
}

int	ft_forward_redirect(char **str)
{
	char		*temp;
	char		*file_name;
	static int	fd;

	if (fd != 0)
	{
		write(1, "fd close\n", 9);
		close(fd);
	}
	temp = ++(*str);
	if (*temp == '>')
		fd = ft_double_redirect(&temp);
	else
	{
		while ((*temp == ' ' || *temp == '\t') && *temp != '\0')
			temp++;
		file_name = ft_parse_arguments(&temp);
		fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		free(file_name);
	}
	*str = temp;
	return (fd);
}

int	ft_reverse_redirect(char **str)
{
	char		*temp;
	char		*file_name;
	static int	fd;

	if (fd > 0)
	{
		write(1, "fd close\n", 9);
		close(fd);
	}
	temp = ++(*str);
	if (*temp == '<' && *(temp + 1) != '\0')
		temp++;
	while ((*temp == ' ' || *temp == '\t') && *temp != '\0')
		temp++;
	file_name = ft_parse_arguments(&temp);
	fd = open(file_name, O_RDONLY, 0644);
	free(file_name);
	*str = temp;
	return (fd);
}