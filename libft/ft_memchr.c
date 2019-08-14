/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:31:05 by hslartib          #+#    #+#             */
/*   Updated: 2019/04/17 20:24:30 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memchr(const void *buffer, int ch, size_t count)
{
	const unsigned char	*str;
	size_t				i;

	i = 0;
	str = buffer;
	while (count)
	{
		if (str[i] == (unsigned char)ch)
			return ((void *)(str + i));
		i++;
		count--;
	}
	return (NULL);
}
