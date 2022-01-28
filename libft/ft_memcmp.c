/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:23:42 by                   #+#    #+#             */
/*   Updated: 2021/10/12 10:23:42 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*l1;
	unsigned char	*l2;
	size_t			i;

	l1 = (unsigned char *)s1;
	l2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (l1[i] != l2[i])
			return (l1[i] - l2[i]);
		i++;
	}
	return (0);
}	
