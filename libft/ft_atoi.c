/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:38:54 by hslartib          #+#    #+#             */
/*   Updated: 2019/04/17 20:15:07 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

long int	ft_atoi(const char *str)
{
	long int	nb;
	int			i;
	int			index;

	i = 0;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\f' || str[i] == '\v'
			|| str[i] == '\r' || str[i] == '\t')
		i++;
	index = str[i] == '-' ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i++] - '0';
		if (index > 0 && i > 20)
			return (-1);
		if (index < 0 && i > 20)
			return (0);
	}
	return ((index * nb));
}
