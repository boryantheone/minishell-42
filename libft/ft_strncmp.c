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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*l1;
	unsigned char	*l2;
	size_t			i;

	l1 = (unsigned char *)s1;
	l2 = (unsigned char *)s2;
	i = 0;
	while ((l1[i] || l2[i]) && (i < n))
	{
		if (l1[i] != l2[i])
			return (l1[i] - l2[i]);
		i++;
	}
	return (0);
}
