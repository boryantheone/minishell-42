#include "../minishell.h"

void ft_skip_quotes(char **str)
{
	char *temp;
	int i;
	
	i = 0;
	temp = ++(*str);
	while (temp[i] && (temp[i] != '\'' && temp[i] != '\"'))
		i++;
	*str = temp + i + 1;
}

void	ft_skip_redirect(char **str)
{
	char	*temp;
	int		i;
	
	i = 0;
	temp = ++(*str);
	if (temp[i] && (temp[i] == '>' || temp[i] == '<'))
		i++;
	while (temp[i] && (temp[i] == ' ' || temp[i] == '\t'))
		i++;
	while (temp[i] && temp[i] != ' ')
		i++;
	*str = temp + i;
}

int ft_limiter(char c)
{
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 62) ||\
		(c >= 91 && c <= 94) || (c >= 124 && c <= 126) \
		|| c == 64 || c == '\0')
		return (1);
	else
		return (0);
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