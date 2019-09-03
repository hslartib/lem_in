/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:01:33 by dbrady            #+#    #+#             */
/*   Updated: 2019/08/14 16:01:34 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

void	append_room(char *str, t_room **rooms, t_info *info)
{
	int		t;
	t_room	*tmp;
	char	**params;

	params = ft_strsplit(str, ' ');
	t = 0;
	tmp = (t_room *)malloc(sizeof(t_room));
	ft_bzero(tmp, sizeof(t_room));
	tmp->links = (int *)malloc(sizeof(int) * 100);
	tmp->links_len = 0;
	tmp->name = ft_strnew(ft_strlen(params[0]));
	ft_memmove(tmp->name, params[0], ft_strlen(params[0]));
	tmp->coord_x = ft_atoi(params[1]);
	tmp->coord_y = ft_atoi(params[2]);
	while (rooms[t])
		t++;
	rooms[t] = tmp;
	info->count_room += 1;
	ft_strdel_2d(&params);
}

int		append_link(char *link, t_room **rooms)
{
	int		f;
	int		s;
	char	**names;

	names = ft_strsplit(link, '-');
	if ((f = rooms_find_name(rooms, names[0])) < 0)
		return (LINK_TO_GHOST);
	if ((s = rooms_find_name(rooms, names[1])) < 0)
		return (LINK_TO_GHOST);
	if (f == s)
	{
		ft_strdel_2d(&names);
		return (0);
	}
	rooms[f]->links_len += 1;
	rooms[f]->links[rooms[f]->links_len - 1] = s;
	rooms[s]->links_len += 1;
	rooms[s]->links[rooms[s]->links_len - 1] = f;
	ft_strdel_2d(&names);
	return (0);
}

int		next_value(t_info *info, char **text, int i)
{
	int se[2];

	ft_bzero(se, sizeof(int) * 2);
	if (!i && info->count_ants == -1)
		return (i);
	i += 1;
	while (text[i] && text[i][0] == '#')
	{
		if (!ft_strcmp(text[i], "##start"))
			se[0] = 1;
		else if (!ft_strcmp(text[i], "##end"))
			se[1] = 1;
		i++;
	}
	if (!text[i])
		return (-1);
	if (se[0] == 1)
		if (info->end != -1)
			return (lem_errmsg(info, MULTIPLE_STARTEND));
	if (se[1] == 1)
		if (info->end != -1)
			return (lem_errmsg(info, MULTIPLE_STARTEND));
	info->start = info->count_room;
	info->end = info->count_room;
	return (i);
}

int		info_init(t_info *info)
{
	int		t;

	ft_bzero(info, sizeof(t_info));
	info->start = -1;
	info->end = -1;
	info->count_ants = -1;
	info->input = read_split();
	if (info_checkorder(info))
		return (MAP_WRONG_ORDER);
	if (!init_rooms(info, info->input))
		return (lem_errmsg(info, NO_ROOMS));
	t = 0;
	if ((t = next_value(info, info->input, t)) == -3)
		return (lem_errmsg(info, MULTIPLE_STARTEND));
	info->count_ants = ft_atoi(info->input[t]);
	while ((t = next_value(info, info->input, t)) >= 0)
	{
		if (ft_strstr(info->input[t], " "))
			append_room(info->input[t], info->rooms, info);
		else if (append_link(info->input[t], info->rooms))
			return (lem_errmsg(info, LINK_TO_GHOST));
	}
	if (t == MULTIPLE_STARTEND)
		return (lem_errmsg(info, MULTIPLE_STARTEND));
	return (info_valid(info));
}
