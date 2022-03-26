/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:24:35 by                   #+#    #+#             */
/*   Updated: 2021/10/12 10:24:35 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_realloc(char *result, int size)
{
	char	*temp;

	temp = result;
	if (result != NULL)
	{
		size += (int)ft_strlen(result);
		result = (char *)ft_calloc(1, (size_t)size);
		ft_strcpy(result, temp);
		free(temp);
	}
	else
		result = (char *)ft_calloc(1, (size_t)size);
	return (result);
}