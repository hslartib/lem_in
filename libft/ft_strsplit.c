/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:59:05 by hslartib          #+#    #+#             */
/*   Updated: 2019/04/18 19:00:24 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int			countmas(char const *s, char c)
{
	int				i;
	int				a;

	i = 0;
	a = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		while (s[i] != c && s[i])
			i++;
		a++;
		while (s[i] == c && s[i])
			i++;
	}
	return (a);
}

static int			lenups(char const *s, char c)
{
	int				i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char			*fun(char **mas, int k, int len, int count)
{
	int				i;

	i = 0;
	if (!(mas[k] = ft_strnew(len + 1)))
	{
		i = 0;
		while (count--)
			free(mas[i++]);
		return (NULL);
	}
	return (mas[k]);
}

static char			**crtmas(char **mas, char const *s, char c, int count)
{
	int				len;
	int				i;
	int				k;

	k = 0;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			len = lenups(s + i, c);
			if (!(mas[k] = fun(mas, k, len, count)))
				return (NULL);
			ft_strncpy(mas[k++], s + i, len);
			s += len;
		}
		while (s[i] == c && s[i])
			i++;
	}
	mas[k] = NULL;
	return (mas);
}

char				**ft_strsplit(char const *s, char c)
{
	int				i;
	int				len;
	char			**mas;

	if (s == NULL)
		return (NULL);
	i = 0;
	len = countmas(s, c);
	if (!(mas = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	mas = crtmas(mas, s, c, len + 1);
	return (mas);
}
