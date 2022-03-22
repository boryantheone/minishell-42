#include "../minishell.h"

void ft_execute(t_var *var, t_list *elem, t_fds *fds)
{
	pid_t pid;
	id_t exit_status;

	if (elem)
	{
		if (elem->next == NULL)
			ft_exec_cmd(elem, var, fds);
		else
		{
			pid = fork();
			if (!pid)
				ft_exec_pipes(var, elem, fds);
			wait(&exit_status);
			if (exit_status == 0)
				var->state = 0;
			if (WIFSIGNALED(exit_status))
				var->state = 128 + exit_status;
			var->state = WEXITSTATUS(exit_status);
		}
	}
	else
		return;
}