/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:23:38 by                   #+#    #+#             */
/*   Updated: 2021/10/14 12:06:28 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	g;

	str = (unsigned char *)s;
	g = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == g)
			return (str + i);
		i++;
	}
	return (0);
}
