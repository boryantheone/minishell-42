#include "../minishell.h"

void	ft_execute(t_var *var, t_list *elem, t_fds *fds)
{
	if (elem)
	{
		if (elem->next == NULL)
			ft_exec_cmd(elem, var, fds);
		else
			ft_exec_pipes(var, elem, fds);
	}
	else
		return ;
}