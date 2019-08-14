/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:28:39 by hslartib          #+#    #+#             */
/*   Updated: 2019/04/17 20:25:28 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char				*ft_revstr(char *a, int n)
{
	char				ho;
	int					i;

	i = 0;
	n -= 1;
	while (i < n)
	{
		ho = a[i];
		a[i++] = a[n];
		a[n] = ho;
		n--;
	}
	return (a);
}

static size_t			dlina(long int n)
{
	size_t				len;

	len = n < 0 ? 1 : 0;
	n *= n < 0 ? -1 : 1;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	len++;
	return (len);
}

char					*ft_itoa(int nb)
{
	long int			n;
	char				*str;
	long int			i;
	long int			index;

	n = nb;
	index = 0;
	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * dlina(n) + 1)))
		return (NULL);
	index = n < 0 ? 1 : 0;
	n *= index ? -1 : 1;
	while (n / 10 != 0)
	{
		str[i++] = n % 10 + '0';
		n /= 10;
	}
	str[i++] = n % 10 + '0';
	i += index ? 1 : 0;
	str = ft_revstr(str, i);
	str[dlina(nb)] = '\0';
	if (index)
		str[0] = '-';
	return (str);
}
