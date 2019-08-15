/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:42:19 by dbrady            #+#    #+#             */
/*   Updated: 2019/06/18 10:19:21 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				gnl_wrtoline(char **fdl, char **line)
{
	char	*tmp;
	int		ret;

	ret = ((ft_strlen(*fdl) != ft_strclen(*fdl, '\n')) ? 1 : 0);
	tmp = NULL;
	(!*line) ? *line = ft_strnew(ft_strclen(*fdl, '\n')) :
	ft_pseudo_realloc((void **)line, ft_strlen(*line),
	(ft_strlen(*line) + ft_strclen(*fdl, '\n') + 1));
	ft_memmove((*line + ft_strlen(*line)), *fdl, ft_strclen(*fdl, '\n'));
	if (ret == 0)
		ft_strdel(fdl);
	else
	{
		tmp = ft_strnew(BUFF_SIZE);
		tmp = ft_memmove(tmp, (*fdl + ft_strclen(*fdl, '\n')
		+ 1), ft_strlen(*fdl));
		ft_strdel(fdl);
		*fdl = tmp;
	}
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	static char *fdm[12000];
	int			ret;

	if (fd < 0 || !line || fd >= 12000)
		return (-1);
	ret = 0;
	*line = NULL;
	(!fdm[fd]) ? (fdm[fd] = ft_strnew(BUFF_SIZE)) : 0;
	if (fdm[fd][0] == '\0')
		if ((read(fd, fdm[fd], BUFF_SIZE)) < 0)
			return (-1);
	while (gnl_wrtoline(&fdm[fd], line) != 1)
	{
		(!fdm[fd]) ? (fdm[fd] = ft_strnew(BUFF_SIZE)) : 0;
		if ((read(fd, fdm[fd], BUFF_SIZE)) == 0)
		{
			ft_strdel(&fdm[fd]);
			(line[0][0] == '\0') ? 0 : (ret = 1);
			return (ret);
		}
	}
	fdm[fd][0] == '\0' ? ft_strdel(&fdm[fd]) : 0;
	return (1);
}
