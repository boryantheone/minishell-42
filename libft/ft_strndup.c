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

char	*ft_strndup(char *src, int len)
{
	char	*result;
	int		i;
	int		str_len;

	i = 0;
	str_len = (int)ft_strlen(src);
	if (len > str_len)
		len = str_len;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (*src && len--)
		result[i++] = *(src++);
	result[i] = '\0';
	return (result);
}
