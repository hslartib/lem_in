/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:34:50 by dbrady            #+#    #+#             */
/*   Updated: 2019/07/25 17:34:50 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dstdst;
	unsigned char	*srcsrc;

	dstdst = (unsigned char *)dst;
	srcsrc = (unsigned char *)src;
	if (dst == src)
		return (dst);
	while (n)
	{
		*dstdst++ = *srcsrc++;
		n--;
	}
	return (dst);
}
