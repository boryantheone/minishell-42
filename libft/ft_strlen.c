/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:24:31 by                   #+#    #+#             */
/*   Updated: 2022/03/21 17:18:52 by dronel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

//size_t	ft_strlen(char *str)
//{
//	size_t	i;
//
//	i = 0;
//	while (str[i] != '\0')
//		i++;
//	return (i);
//}
//size_t		ft_strlen(char *str)
//{
//	char	*str_copy = str;
//
//	while (str && *str)
//		str++;
//	return ((size_t)(str - str_copy));
//}
size_t	ft_strlen(char *str)
{
	size_t	size;

	size = 0;
	while (*str)
	{
		size++;
		str++;
	}
	return (size);
}