/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:24:05 by                   #+#    #+#             */
/*   Updated: 2022/03/09 19:31:52 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

//char	*ft_strdup(const char *s1)
//{
//	const char		*str;
//	unsigned int	i;
//
//	str = (char *)s1;
//	i = ft_strlen((char *)s1) + 1;
//	str = (char *)malloc(i * sizeof(char));
//	if (!str)
//		return (NULL);
//	str = ft_memcpy((char *)str, (char *)s1, i);
//	return ((char *)str);
//}
char	*ft_strdup(const char *src)
{
	char	*result;
	size_t	i;

	i = 0;
	if (!(result = (char*)malloc(sizeof(char) * (ft_strlen((char *)src) + 1))))
		return (NULL);
	while (*src)
		result[i++] = *(src++);
	result[i] = '\0';
	return (result);
}