#include "../minishell.h"

void	ft_execute(t_var *var, t_list *elem)
{
	if(elem)
	{
		if (elem->next == NULL)
			ft_exec_cmd(elem, var);
		else
			ft_exec_pipes(var, elem);
	}
	else
		return ;
}