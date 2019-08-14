/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 14:34:17 by hslartib          #+#    #+#             */
/*   Updated: 2019/05/03 19:04:57 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_jon		*list(const int fd)
{
	t_jon			*kong;

	if (!(kong = (t_jon *)malloc(sizeof(t_jon))))
		return (0);
	(kong)->svd = fd;
	if (!((kong)->mod = (char *)malloc(sizeof(1))))
		return (0);
	*((kong)->mod) = '\0';
	(kong)->next = NULL;
	return (kong);
}

static t_jon		*work_with_struct(const int fd, t_jon **mor)
{
	t_jon			*kong;

	kong = *mor;
	if (!kong)
	{
		if (!(kong = list(fd)))
			return (0);
		*mor = kong;
	}
	while (fd != (kong)->svd && (kong)->next)
		(kong) = (kong)->next;
	if (fd != (kong)->svd)
	{
		if (!(kong->next = list(fd)))
			return (0);
		kong = kong->next;
	}
	return (kong);
}

static int			work_with_mod(t_jon *kong, int fd)
{
	char			mart[BUFF_SIZE + 1];
	char			*norm;
	int				r;

	fd = (kong)->svd;
	r = read((kong)->svd, mart, BUFF_SIZE);
	mart[r] = '\0';
	if (r == -1)
		return (-1);
	if (r == 0)
		return (0);
	norm = (kong)->mod;
	if (!((kong)->mod = ft_strjoin((kong)->mod, mart)))
		return (-1);
	free(norm);
	return (100);
}

static int			find_n(t_jon **kong, char **line)
{
	int				m;
	char			*lom;
	char			*venom;
	size_t			len;

	while (!(lom = ft_memchr((*kong)->mod, '\n', ft_strlen((*kong)->mod))))
	{
		m = work_with_mod(*kong, (*kong)->svd);
		if (m == 0 && ft_strlen((*kong)->mod) > 0)
			return (!(*line = ft_strdup((*kong)->mod)) ||
			!((*kong)->mod = ft_strnew(0)) ? -1 : 0);
		else if (m == 0)
			return (!(*line = ft_strnew(0)) ? -1 : 0);
		else if (m == -1)
			return (-1);
	}
	len = lom - (*kong)->mod;
	if (!(*line = ft_strsub((*kong)->mod, 0, len)))
		return (-1);
	venom = (*kong)->mod;
	if (!((*kong)->mod = ft_strsub((*kong)->mod, len + 1,
			ft_strlen((*kong)->mod) - (len + 1))))
		return (-1);
	free(venom);
	return (100);
}

int					get_next_line(const int fd, char **line)
{
	static t_jon	*kong;
	t_jon			*lord;
	int				pup;

	if (fd < 0 || !line)
		return (-1);
	lord = work_with_struct(fd, &kong);
	pup = find_n(&lord, line);
	if (!pup && ft_strlen(*line) > 0)
		return (1);
	else if (!pup)
	{
		free(kong->mod);
		free(kong);
		return (0);
	}
	else if (pup == -1)
		return (-1);
	return (1);
}
