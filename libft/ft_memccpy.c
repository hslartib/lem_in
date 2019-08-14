/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:12:00 by hslartib          #+#    #+#             */
/*   Updated: 2019/04/17 19:07:59 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*a;
	unsigned const char	*b;

	a = (unsigned char *)dst;
	b = (unsigned char const*)src;
	while (n)
	{
		*a = *b;
		if (*a == (unsigned char)c)
			return (++a);
		a++;
		b++;
		n--;
	}
	return (NULL);
}
