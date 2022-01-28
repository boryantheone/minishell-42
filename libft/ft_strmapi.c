/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:46:22 by                   #+#    #+#             */
/*   Updated: 2021/10/13 09:43:52 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*des;
	unsigned int	i;
	unsigned int	size;

	i = 0;
	if (!s)
		return (NULL);
	size = ft_strlen((char *)s);
	des = malloc(sizeof(char) + (size));
	if (!des)
		return (NULL);
	while (i < size)
	{
		des[i] = ((*f)(i, s[i]));
		i++;
	}
	des[size] = '\0';
	return (des);
}
