
#include "../minishell.h"

t_fds	*ft_fdsnew(int fd_read, int fd_write, int heredoc)
{
	t_fds	*node;

	node = (t_fds *)malloc(sizeof(t_fds));
	if (!node)
		return (NULL);
	node -> fd_in = fd_read;
	node -> fd_out = fd_write;
	node -> fd_heredoc = heredoc;
	node -> next = NULL;
	return (node);
}

void	ft_fdsadd_back(t_fds **lst, t_fds *new)
{
	t_fds	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp -> next != NULL)
		tmp = tmp -> next;
	tmp -> next = new;
}

static char	*ft_replace_return(char *result)
{
	free(result);
	return ("\0");
}

char	*ft_replace_env(char *str)
{
	int			index;
	char		*result1;
	static char	*result;

	index = 0;
	result1 = NULL;
	while (str[index] && str[index] != '$')
		index++;
	if (index)
		result = ft_strndup(str, index);
	else
		result = ft_strdup("\0");
	str = str + index;
	result1 = ft_parse_with_envp(&str, 1);
	if (!result1)
	{
		free(result);
		return ("\0");
	}
	result = ft_my_strjoin(result, result1);
	free(result1);
	index = 0;
	while (str[index] != '\0')
		index++;
	result1 = ft_strndup(str, index);
	result = ft_my_strjoin(result, result1);
	free(result1);
	return (result);
}
