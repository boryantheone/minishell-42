/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:23:03 by                   #+#    #+#             */
/*   Updated: 2021/10/12 10:23:03 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*str;
	unsigned int	nbytes;

	nbytes = count * size;
	str = malloc(nbytes);
	if (str)
		ft_memset(str, 0, nbytes);
	return (str);
}
