/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:40:40 by hslartib          #+#    #+#             */
/*   Updated: 2019/04/17 20:18:28 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			cutlen(int len, char const *s)
{
	int				i;

	i = 0;
	while (s[i] == '\n' || s[i] == ' ' || s[i] == '\t')
	{
		len -= 1;
		i++;
	}
	if (!(s[i]))
		return (0);
	i = ft_strlen(s) - 1;
	while (s[i] == '\n' || s[i] == ' ' || s[i] == '\t')
	{
		len -= 1;
		i--;
	}
	return (len);
}

static char			*cpycut(char *str, char const *s, int len)
{
	int				i;

	i = 0;
	while (s[i] == '\n' || s[i] == ' ' || s[i] == '\t')
		i++;
	ft_memcpy(str, s + i, len);
	str[len] = '\0';
	return (str);
}

char				*ft_strtrim(char const *s)
{
	int				len;
	char			*str;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	len = cutlen(len, s);
	if (!(str = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	str = cpycut(str, s, len);
	return (str);
}
