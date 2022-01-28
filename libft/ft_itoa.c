/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dronel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:44:57 by dronel            #+#    #+#             */
/*   Updated: 2021/10/13 12:49:05 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lennbr(long int nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	if (nb == 0)
		i++;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	nl;

	nl = n;
	i = ft_lennbr(nl);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	if (nl < 0)
	{
		nl *= -1;
		str[0] = '-';
	}
	str[i] = '\0';
	if (nl == 0)
		str[i - 1] = '0';
	while (nl > 0)
	{
		str[i - 1] = (nl % 10) + '0';
		nl /= 10;
		i--;
	}
	return (str);
}
