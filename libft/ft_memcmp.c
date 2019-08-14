/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:44:20 by hslartib          #+#    #+#             */
/*   Updated: 2019/04/17 18:54:26 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char		a;
	unsigned char		b;

	while (n--)
	{
		a = *(unsigned char *)s1;
		b = *(unsigned char *)s2;
		if (a != b)
			return (a - b);
		s1++;
		s2++;
	}
	return (0);
}
