/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_delite_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:11:35 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/06 20:11:36 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

void				room_in_time_copy(t_room *room, t_info *info, int index)
{
	info->time[index] = room;
	info->time[index]->rebuild = 0;
}

void				fill_rest(t_info *info)
{
	int				i;

	i = 0;
	while (i < info->count_time)
	{
		if (!info->time[i])
			room_in_time_copy(info->rooms[i], info, i);
		i++;
	}
}

void				init_time(t_info *info, t_path *path)
{
	int				v;
	int				w;

	w = 0;
	info->count_time = 0;
	while (w < path->count_root)
	{
		info->count_time += path->len_root[w];
		w++;
	}
	info->count_time -= (w * 2);
	info->count_time += info->count_room;
	info->time = (t_room **)malloc(sizeof(t_room *) * info->count_time);
	v = 0;
	while (v < info->count_room)
	{
		info->time[v] = NULL;
		v++;
	}
}

void				init_v(t_info *info, int v, int kl)
{
	info->time[v] = (t_room *)malloc(sizeof(t_room));
	info->time[v]->index = v;
	info->time[v]->links_len = 1;
	info->time[v]->links = (int *)malloc(sizeof(int));
	info->time[v]->rebuild = -1;
	info->time[v]->true_index = kl;
	if (info->time[kl] == NULL)
		info->time[kl] = (t_room *)malloc(sizeof(t_room));
	else
	{
		free(info->time[kl]->links);
		free(info->time[kl]);
		info->time[kl] = (t_room *)malloc(sizeof(t_room));
	}
	info->time[kl]->index = kl;
	info->time[kl]->links_len = info->rooms[kl]->links_len - 1;
	info->time[kl]->links = (int *)malloc(sizeof(int)
											  * info->time[kl]->links_len);
	info->time[kl]->rebuild = 10;
}

void				init_start(t_info *info, t_path *path)
{
	int				z;
	int				w;

	info->time[info->start] = (t_room *)malloc(sizeof(t_room));
	info->time[info->start]->index = info->start;
	info->time[info->start]->links_len =
		info->rooms[info->start]->links_len - path->count_root;
	info->time[info->start]->links = (int *)malloc(sizeof(int) *
		info->time[info->start]->links_len);
	info->time[info->start]->rebuild = 1;
	w = 0;
	z = 0;
	while (z < info->rooms[info->start]->links_len)
	{
		if (check_start_time(info->rooms[info->start]->links[z], path))
			info->time[info->start]->links[w++] =
				info->rooms[info->start]->links[z];
		z++;
	}
}