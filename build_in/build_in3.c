/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:50:15 by jcollin           #+#    #+#             */
/*   Updated: 2022/03/26 15:50:16 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_help_lstdelone(t_envp **tmp, t_envp **begin)
{
	t_envp	*del;

	if ((*begin) == (*tmp))
		*begin = (*tmp)->next;
	else
	{
		del = *begin;
		while (del && del->next != (*tmp))
			del = del->next;
		if (del)
			del->next = (*tmp)->next;
	}
	if ((*tmp)->var)
		free((*tmp)->var);
	if ((*tmp)->val)
		free((*tmp)->val);
	free(*tmp);
}

static void	ft_lstdelone_envp(t_list *elem, int j, int index)
{
	t_envp	*tmp;
	t_envp	*begin;

	if (j == 1)
		begin = g_var->envp;
	else
		begin = g_var->export;
	tmp = begin;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->var, elem->cmds[index]) == 0)
		{
			ft_help_lstdelone(&tmp, &begin);
			continue ;
		}
		tmp = tmp->next;
	}
}

int	ft_unset(t_list *elem)
{
	int	i;

	i = 1;
	while (elem->cmds[i] != NULL)
	{
		if (ft_isalpha(elem->cmds[i]))
		{
			ft_lstdelone_envp(elem, 0, i);
			ft_lstdelone_envp(elem, 1, i);
		}
		else
		{
			ft_putstr_fd("minishelchik: bash: `", STDERR_FILENO);
			ft_putstr_fd(elem->cmds[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			g_var->state = 1;
			return (EXIT_FAILURE);
		}
		i++;
	}
	g_var->state = 0;
	return (EXIT_SUCCESS);
}

static int	ft_cd_change_pwd(char *new_pwd, char *prev_pwd, t_envp **env)
{
	t_envp	*tmp;
	char	pwd[MAXDIR];

	tmp = *env;
	while (tmp)
	{
		if ((!ft_strncmp(tmp->var, "PWD", 3)))
		{
			getcwd(pwd, MAXDIR);
			if (!(ft_strcmp(new_pwd, "..")))
				tmp->val = pwd;
			else
				tmp->val = new_pwd;
		}
		tmp = tmp->next;
	}
	ft_cd_change_oldpwd(env, prev_pwd);
	free(tmp);
	return (EXIT_FAILURE);
}

int	ft_cd(t_list *elem)
{
	char	prev_pwd[MAXDIR];

	getcwd(prev_pwd, MAXDIR);
	if (elem->cmds[1] == NULL || !(ft_strncmp(elem->cmds[1], "~", 1)))
	{
		chdir(getenv("HOME"));
		return (EXIT_SUCCESS);
	}
	if (chdir(elem->cmds[1]) == -1)
	{
		write(1, "error\n", 6);
		return (ft_display_error("cd", elem->cmds[1]));
	}
	else
		ft_cd_change_pwd(elem->cmds[1], prev_pwd, &g_var->envp);
	g_var->state = 0;
	return (EXIT_SUCCESS);
}
