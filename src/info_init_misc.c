/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_init_misc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 02:06:52 by dbrady            #+#    #+#             */
/*   Updated: 2019/08/15 02:06:53 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

int				rooms_find_name(t_room **rooms, char *name)
{
	int r;

	r = 0;
	while (rooms[r] && ft_strcmp(rooms[r]->name, name))
		r++;
	return (rooms[r] ? r : -1);
}

static int		info_islink(char *line)
{
	char	**tmp;
	int		i;
	int		ret;

	i = 0;
	if (ft_strstr(line, " "))
		return (0);
	tmp = ft_strsplit(line, '-');
	while (tmp[i])
		i++;
	if (i != 2)
		ret = 0;
	else
		ret = 1;
	ft_strdel_2d(&tmp);
	return (ret);
}

int				init_rooms(t_info *info, char **text)
{
	int		runner;
	int		len;

	runner = next_value(info, text, 0) + 1;
	len = 0;
	while (text[runner] && !info_islink(text[runner]))
	{
		if (ft_strstr(text[runner], "-"))
			return (lem_errmsg(info, ROOM_INVALID_NAME));
		if (text[runner][0] != '#')
			len += 1;
		runner += 1;
	}
	if (!text[runner] && !len)
		return (lem_errmsg(info, EMPTY));
	if (!text[runner])
		return (lem_errmsg(info, NO_LINKS));
	info->rooms = (t_room **)malloc(sizeof(t_room *) * (len + 1));
	ft_bzero(info->rooms, sizeof(t_room *) * (len + 1));
	return (len ? ALLRIGHT : lem_errmsg(info, NO_ROOMS));
}

char			**read_split(void)
{
	char	**tmp;
	int		t;

	t = -1;
	tmp = (char **)malloc(sizeof(char *) * 100000);
	while (++t < 100000)
		tmp[t] = NULL;
	t = 0;
	while (get_next_line(0, tmp + t) > 0)
		t++;
	free(tmp[t]);
	tmp[t] = NULL;
	return (tmp);
}
