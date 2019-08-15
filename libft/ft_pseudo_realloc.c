/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pseudo_realloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:57:05 by dbrady            #+#    #+#             */
/*   Updated: 2019/06/18 10:19:21 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_pseudo_realloc(void **ptr, size_t size_old, size_t size_new)
{
	void *new;

	if (size_new == 0)
	{
		free(ptr);
		ptr = NULL;
	}
	new = malloc(size_new);
	ft_bzero(new, size_new);
	ft_memmove(new, *ptr, (size_old + 1));
	free(*ptr);
	ptr[0] = new;
}
