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

void ft_printfds(t_fds *elem)
{
	t_fds *tmp;
	
	tmp = elem;
//	write(2, "++++++++++++++++++++++++\n", 26);
	if(elem)
	{
		while (tmp != NULL)
		{
			printf("fd_out(write) %d, fd_in(read) %d heredoc %d "
				   "|", tmp->fd_out, tmp->fd_in, tmp->fd_heredoc);
			tmp = tmp->next;
		}
	}
	else
		printf("elem not found\n");
	printf("\n----------------------\n");
}

int	ft_heredoc(char **str)
{
	char	*document;
	char	*tmp;
	int		fd_heredoc;
	
	
}

void ft_parser_fds(char *str)
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
		else if (*str == '<' && *(str + 1) == '<')
		{
			fd_heredoc = ft_heredoc(&str);
//			write(1, "<\n", 2);
		}
		else
			str++;
	}
	if (*str == '\0')
		ft_fdsadd_back(&fds, ft_fdsnew(0,0,fd_heredoc));
	ft_printfds(fds);
	printf("end of heredoc perser\n");
}

