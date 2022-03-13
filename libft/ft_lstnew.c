/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:52:16 by                   #+#    #+#             */
/*   Updated: 2022/03/09 09:40:40 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char **arg, int fd_read, int fd_write, int pipe, int
have_heredoc)
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
	node -> fd_in = fd_read;
	node -> fd_out = fd_write;
	node -> have_pipe = pipe;
	node -> have_heredoc = have_heredoc;
	node -> next = NULL;
	return (node);
}