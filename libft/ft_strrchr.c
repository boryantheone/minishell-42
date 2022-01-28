/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:24:46 by                   #+#    #+#             */
/*   Updated: 2021/10/14 16:50:12 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*found;

	i = 0;
	found = NULL;
	if (s[i] == '\0' && c != '\0')
		return (NULL);
	if (!*(char *)s)
		found = (char *)(s + i);
	while (*(char *)(s + i))
	{
		if (*(char *)(s + i) == (char )c)
		{
			found = (char *)(s + i);
		}
		i++;
	}
	if (*(char *)(s + i) == (char )c)
		return ((char *)(s + i));
	return (found);
}
