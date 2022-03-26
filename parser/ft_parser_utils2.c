
#include "../minishell.h"

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

int	ft_str_double_len(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

int	ft_check_fds(t_fds *fds)
{
	t_fds	*tmp_fds;

	tmp_fds = fds;
	if (tmp_fds != NULL)
	{
		if (tmp_fds->fd_in == -1 || tmp_fds->fd_out == -1)
			return (-1);
		return (EXIT_SUCCESS);
	}
	return (-1);
}

char	*ft_my_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = (int)ft_strlen((char *)s1);
	j = (int)ft_strlen((char *)s2);
	str = malloc(sizeof(char) * (i + j + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

int	ft_perror_heredoc(char **stop, int flag)
{
	g_var->state = 258;
	if (flag == 0)
		printf("minishelchik: syntax error near unexpected token `newline'\n");
	else
	{
		free(*stop);
		printf("minishelchik: syntax error near unexpected token `<<'\n");
	}
	return (-1);
}
