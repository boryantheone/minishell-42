/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:37:25 by                   #+#    #+#             */
/*   Updated: 2022/03/09 09:40:40 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*l;
	t_list	*save;

	l = *lst;
	while (l)
	{
		save = l->next;
		ft_lstdelone(l);
		l = save;
	}
	*lst = NULL;
}

void	ft_lstclear_fds(t_fds **lst)
{
	t_fds	*l;
	t_fds	*save;

	if (lst == NULL)
		return ;
	l = *lst;
	while (l && l->next)
	{
		save = l->next;
		free(l);
		l = save;
	}
	free(l);
	*lst = NULL;
}
