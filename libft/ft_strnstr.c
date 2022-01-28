/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:24:40 by                   #+#    #+#             */
/*   Updated: 2021/10/12 10:24:40 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str1;
	char	*str2;
	size_t	i;
	size_t	j;
	size_t	len_h;

	str1 = (char *)haystack;
	str2 = (char *)needle;
	i = 0;
	len_h = ft_strlen((char *)needle);
	if (len_h == 0 || str1 == str2)
		return ((char *)(str1 + i));
	while (str1[i] != '\0')
	{
		j = 0;
		while (str1[i + j] == str2[j] && str1[i + j] != '\0'\
				&& str2[j] != '\0' && i + j < len)
			j++;
		if (j == len_h)
			return ((char *)(str1 + i));
		i++;
	}
	return (NULL);
}
