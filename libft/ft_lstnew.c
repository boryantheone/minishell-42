/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:52:16 by                   #+#    #+#             */
/*   Updated: 2022/03/13 15:28:27 by jcollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char **arg)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	if (arg)
	{
		node -> cmd = arg[0];
		node -> cmds = arg;
	}
	else
	{
		node->cmd = NULL;
		node->cmds = NULL;
	}
	node -> path = NULL;
	node -> next = NULL;
	return (node);
}
