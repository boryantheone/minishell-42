#include "../minishell.h"

void	ft_execute(t_var *var, t_list *elem, t_fds *fds)
{
	pid_t pid;
	
	if (elem)
	{
		if (elem->next == NULL)
			ft_exec_cmd(elem, var, fds);
		else
		{
			pid = fork();
			if(!pid)
				ft_exec_pipes(var, elem, fds);
			wait(0);
		}
	}
	else
		return ;
}