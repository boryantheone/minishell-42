#include "../minishell.h"

void ft_execute(t_list *elem, t_fds *fds)
{
	pid_t pid;
	id_t exit_status;

	if (elem)
	{
		if (elem->next == NULL)
			ft_exec_cmd(elem, fds);
		else
		{
			pid = fork();
			if (!pid)
				ft_exec_pipes(elem, fds);
			wait(&exit_status);
			if (exit_status == 0)
				g_var->state = 0;
			if (WIFSIGNALED(exit_status))
				g_var->state = 128 + exit_status;
			g_var->state = WEXITSTATUS(exit_status);
		}
	}
	else
		return;
}