#include "../minishell.h"

void ft_lstdelone_envp(t_var *var, t_list *elem, int j, int	index)
{
	t_envp	*tmp;
	t_envp	*begin;
	t_envp	*del;
	int		i;
	
	i = 1;
	if (j == 1)
		begin = var->envp;
	else
		begin = var->export;
	tmp = begin;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->var, elem->cmds[index]) == 0)
		{
			if (begin == tmp)
				begin = tmp->next;
			else
			{
				del = begin;
				while (del && del->next != tmp)
					del = del->next;
				if (del)
					del->next = tmp->next;
			}
			if (tmp->var)
				free(tmp->var);
			if (tmp->val)
				free(tmp->val);
			free(tmp);
			continue ;
		}
		tmp = tmp->next;
	}
}

int ft_unset(t_var *var, t_list *elem)
{
	t_envp *tmp;
	int i;
	
	i = 1;
	while (elem->cmds[i] != NULL)
	{
		if (ft_isalpha(elem->cmds[i]))
		{
			ft_lstdelone_envp(var, elem, 0, i);
			ft_lstdelone_envp(var, elem, 1, i);
		}
		else
		{
			ft_putstr_fd("minishelchik: bash: `", STDERR_FILENO);
			ft_putstr_fd(elem->cmds[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			var->state = 1;
			return (EXIT_FAILURE);
		}
		i++;
	}
	var->state = 0;
	return (EXIT_SUCCESS);
}
