/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcollin <jcollin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:24:00 by                   #+#    #+#             */
/*   Updated: 2022/03/09 09:40:40 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strchr(char *s, char c)
{
	char	*str;
	char	g;

	str = (char *)s;
	g = (char)c;
	while (*str)
	{
		if (*str == g)
			return (1);
		else
			str++;
	}
	if (*str == g)
		return (1);
	return (0);
}
