
#include "../minishell.h"


char	*ft_remove_quotes(char *str)
{
	int		index;
	int		end;
	char	*result1;
	char	*result;

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
	result = ft_my_strjoin(result, result1);
	free(result1);
	index = ++end;
	while (str[end] != '\0')
		end++;
	result1 = ft_substr(str, index, end - index);
	result = ft_my_strjoin(result, result1);
	free(result1);
	return (result);
}

void	ft_child_heredoc(int fd, char *stop)
{
	char	*result;

	ft_init_signal_handler(ft_handler_heredoc);
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_IGN);
	result = readline("> ");
	while (result && ft_strncmp(result, stop, ft_strlen(stop) + 1))
	{
		while ((ft_strchr(result, '$')))
			result = ft_replace_env(result);
		write(fd, result, ft_strlen(result));
		write(fd, "\n", 1);
		if (result)
			free(result);
		result = readline("> ");
	}
	if (result)
		free(result);
	close (fd);
	exit(EXIT_SUCCESS);
}

int	ft_heredoc(char **str)
{
	char			*tmp;
	char			*stop;
	char			*clean;
	static int		fd_heredoc;
	int				index;
	pid_t			pid;
	int 			status;

	index = 0;
	if (fd_heredoc != 0)
		close(fd_heredoc);
	tmp = *str + 2;
	while ((*tmp == ' ' || *tmp == '\t') && *tmp != '\0')
		tmp++;
	while (tmp[index] != ' ' && tmp[index] != '\0' && tmp[index] != '|')
		index++;
	if (!index)
	{
		printf("minishelchik: syntax error near unexpected token `newline'\n");
		g_var->state = 258;
		return (-1);
	}
	clean = ft_strndup(tmp, index);
	stop = ft_remove_quotes(clean);
	free(clean);
	unlink("here_document");
	fd_heredoc = open("here_document", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_heredoc == -1)
		return (ft_perror("heredoc", -1));
	rl_catch_signals = 1;
	pid = fork();
	if (!pid)
		ft_child_heredoc(fd_heredoc, stop);
	else
	{
	// 	signal(SIGINT, SIG_IGN);
	// 	// ft_init_signal_handler(ft_handler_heredoc);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(0, NULL, 0);
	}
	rl_catch_signals = 0;
	ft_init_signal_handler(ft_handler_main);
	*str = tmp;
	close(fd_heredoc);
	fd_heredoc = open("here_document", O_RDONLY, 0644);
	free(stop);
	if (fd_heredoc == -1)
		return (ft_perror("heredoc", -1));
	return (fd_heredoc);
}

t_fds	*ft_parser_heredoc(char *str)
{
	t_fds	*fds;
	int		fd_heredoc;

	fd_heredoc = 0;
	fds = NULL;
	while (*str)
	{
		if (*str == '|')
		{
			ft_fdsadd_back(&fds, ft_fdsnew(0, 0, fd_heredoc));
			fd_heredoc = 0;
			str++;
		}
		if (*str == '\"' || *str == '\'')
			ft_skip_quotes(&str);
		else if (*str == '<' && *(str + 1) == '<')
		{
			fd_heredoc = ft_heredoc(&str);
			if (fd_heredoc == -1)
			{
				g_var->state = 258;
				return (NULL);
			}
		}
		else
			str++;
	}
	if (*str == '\0')
		ft_fdsadd_back(&fds, ft_fdsnew(0, 0, fd_heredoc));
	return (fds);
}
