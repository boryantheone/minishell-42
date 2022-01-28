/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:32:52 by                   #+#    #+#             */
/*   Updated: 2021/10/12 13:43:09 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len_s1;
	size_t	i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	len_s1 = ft_strlen((char *)s1) - 1;
	if (i > len_s1)
		return (str = ft_strdup("\0"));
	while (s1[len_s1] && ft_strrchr(set, s1[len_s1]))
		len_s1--;
	str = ft_substr(&s1[i], 0, (len_s1 - i + 1));
	return (str);
}
