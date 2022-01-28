/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:24:05 by                   #+#    #+#             */
/*   Updated: 2021/10/12 10:24:05 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	const char		*str;
	unsigned int	i;

	str = (char *)s1;
	i = ft_strlen((char *)s1) + 1;
	str = (char *)malloc(i * sizeof(char));
	if (!str)
		return (NULL);
	str = ft_memcpy((char *)str, (char *)s1, i);
	return ((char *)str);
}
