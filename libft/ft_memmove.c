/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:09:01 by hslartib          #+#    #+#             */
/*   Updated: 2019/04/12 17:20:06 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	int i;

	i = 0;
	if (src < dst)
	{
		while (len)
		{
			*(unsigned char *)(dst + len - 1) =
				*(unsigned char *)(src + len - 1);
			len--;
		}
	}
	else
	{
		while (len)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i++;
			len--;
		}
	}
	return (dst);
}
