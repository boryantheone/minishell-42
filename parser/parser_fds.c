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

char	*ft_remove_quotes(char *str)
{
	int		index;
	int 	end;
	char	*result1;
	char 	*result;
	
	index = 0;
	while (str[index] && (str[index] != '\'' && str[index] != '\"'))
		index++;
	if (index)
		result = ft_strndup(str, index);
	else
		result = ft_strdup("\0");
	end = index + 1;
	while (str[end] && (str[end] != '\'' && str[end] != '\"'))
		end++;	
	result1 = ft_substr(str, index + 1, end - index - 1);
	result = ft_strjoin(result, result1);
	free(result1);
	index = ++end;
	while (str[end] != '\0')
		end++;
	result1 = ft_substr(str, index, end - index);
	result = ft_strjoin(result, result1);
	free(result1);
	return (result);
}

char	*ft_replace_env(char *str)
{
	int		index;
	int 	end;
	char	*result1;
	static char 	*result;

	index = 0;
	result1 = NULL;
//	printf("1 str search index $ %s\n", str);
	while(str[index] && str[index] != '$')
		index++;
	if (index)	
		result = ft_strndup(str, index);
	else
		result = ft_strdup("\0");
	str = str + index;
//	printf("1 str %s\n", str);
//	printf("1 result |%s|\n", result);
	result1 = ft_parse_with_envp(&str, 1);
//	printf("1 result1 after perse env %s\n", result1);
	if (!result1)
	{
		free(result);
		return ("\0");
	}
	result = ft_strjoin(result, result1);
	free(result1);
	index = 0;
	while (str[index] != '\0')
		index++;
	result1 = ft_strndup(str, index);
	result = ft_strjoin(result, result1);
	free(result1);
//	printf("resul replace %s\n", result);
//	write(1, "====================\n", 21);
	return (result);
}

int	ft_heredoc(char **str)
{
	char			*result;
	char			*tmp;
	char			*stop;
	static int		fd_heredoc;
	int 			index;
	
	index = 0;
	if (fd_heredoc != 0)
		close(fd_heredoc);
	tmp = *str + 2;
//	printf("tmp %s\n", tmp);
	while ((*tmp == ' ' || *tmp == '\t') && *tmp != '\0')
		tmp++;
	while (tmp[index] != ' ' && tmp[index] != '\0' && tmp[index] != '|')
		index++;
	if (!index)
	{
		printf("minishelchik: syntax error near unexpected token `newline'\n");
		var->state = 258;
		return (-1);
	}
	unlink(".here_document");
	fd_heredoc = open(".here_document", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd_heredoc == -1)
		return (ft_perror("heredoc", -1));
	stop = ft_strndup(tmp, index);
//	printf("stop %s\n", stop);
	stop = ft_remove_quotes(stop);
	result = readline("> ");
	while (ft_strncmp(result, stop, ft_strlen(stop) + 1))
	{
		while ((ft_strchr(result, '$')))
			result = ft_replace_env(result);
//		write(1, result, ft_strlen(result));
		write(fd_heredoc, result, ft_strlen(result));
		write(fd_heredoc, "\n", 1);
		result = readline("> ");
	}
	*str = tmp;
	return(fd_heredoc);
}

t_fds	*ft_parser_heredoc(char *str)
{
	t_fds	*fds;
	static int	fd_heredoc;

	fd_heredoc = 0;
	fds = NULL;
	while (*str)
	{
		if (*str == '|')
		{
			ft_fdsadd_back(&fds, ft_fdsnew(0,0,fd_heredoc));
			fd_heredoc = 0;
			str++;
		}
		if (*str == '\"' || *str == '\'')
			ft_skip_quotes(&str);
		else if (*str == '<' && *(str + 1) == '<')
		{
			fd_heredoc = ft_heredoc(&str);
			if(fd_heredoc == -1)
			{
				var->state = 258;
				return (NULL);
			}
		}
		else
			str++;
	}
	if (*str == '\0')
		ft_fdsadd_back(&fds, ft_fdsnew(0,0,fd_heredoc));
	return (fds);
}

