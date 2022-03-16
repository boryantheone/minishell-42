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