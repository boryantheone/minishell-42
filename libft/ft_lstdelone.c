/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:19:35 by                   #+#    #+#             */
/*   Updated: 2022/03/09 09:40:40 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../minishell.h"

void	ft_lstdelone(t_list *lst)
{
	if (!lst)
		return ;
	else
	{
		if (lst->cmd)
			free(lst->cmd);
		if(lst->path)
			free(lst->path);
		if(lst->cmds)
			free(lst->cmds);
		//free (lst);
	}
}
