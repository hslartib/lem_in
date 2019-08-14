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

#include "./inc/lem_strt.h"

char	**read_split()
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
	tmp[t] = NULL;
	return (tmp);
}

int		rooms_find_name(t_room **rooms, char *name)
{
	int r;

	r = 0;
	while (rooms[r] && ft_strcmp(rooms[r]->name, name))
		r++;
	return (rooms[r] ? r : -1);
}

void	append_room(char *str, t_room **rooms, t_info *info)
{
	int		t;
	t_room	*tmp;
	char	*name;

	name = ft_strnew(ft_strclen(str, ' '));
	ft_memmove(name, str, ft_strclen(str, ' '));
	t = 0;
	tmp = (t_room *)malloc(sizeof(t_room));
	tmp->links = (int *)malloc(sizeof(int) * 100);
	tmp->links_len = 0;
	tmp->name = name;
	while (rooms[t])
		t++;
	rooms[t] = tmp;
	info->count_room += 1;
}

int		append_link(char *link, t_room **rooms)
{
	int		f;
	int		s;
	char	**names;

	names = ft_strsplit(link, '-');
	if ((f = rooms_find_name(rooms, names[0])) < 0)
		return (-1);
	if ((s = rooms_find_name(rooms, names[1])) < 0)
		return (-1);
	rooms[f]->links_len += 1;
	rooms[f]->links[rooms[f]->links_len - 1] = s;
	rooms[s]->links_len += 1;
	rooms[s]->links[rooms[s]->links_len - 1] = f;
	return (0);
}

int 	next_value(t_info *info, char **text, int i)
{
	int se[2];

	ft_bzero(se, sizeof(int) * 2);
	if (!i && info->count_ants == -1)
		return(i);
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
	(se[0] == 1 && !info->start) ? info->start = info->count_room : 0;
	(se[1] == 1 && !info->end) ? info->end = info->count_room : 0;
	return (i);
}

void	info_init(t_info *info)
{
	t_room	**rooms;
	char 	**text;
	int 	t;

	ft_bzero(info, sizeof(t_info));
	info->count_ants = -1;
	text = read_split();
	rooms = (t_room **)malloc(sizeof(t_room *) * 24000);
	t = -1;
	while (++t < 24000)
		rooms[t] = NULL;
	t = 0;
	if ((t = next_value(info, text, t)) >= 0)
		info->count_ants = ft_atoi(text[t]);
	while ((t = next_value(info, text, t)) >= 0)
	{
		if (ft_strstr(text[t], " "))
			append_room(text[t], rooms, info);
		else
			append_link(text[t], rooms);
	}
}