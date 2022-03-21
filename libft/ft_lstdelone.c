/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:19:35 by                   #+#    #+#             */
/*   Updated: 2022/03/21 17:18:52 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

void	ft_lstdelone(t_list *lst)
{
	int i;
	
	i = 0;
	if (!lst)
		return ;
	else
	{
		if (lst->cmd)
			free(lst->cmd);
		if(lst->path && (ft_strcmp(lst->path, "command not found")))
			free(lst->path);
//		if(lst->cmds)
//		{
//			while (lst->cmds[i])
//			{
//				free(lst->cmds[i]);
//				i++;
//			}
//			free(lst->cmds);
//		}
	}
}
