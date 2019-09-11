/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:10:07 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/06 20:10:33 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

int					delite_prt1(t_info *info, t_path *path, int coo, int v)
{
	int z;
	int w;
	int i;
	int k;

	i = coo / 1000000;
	k = coo % 1000000;
	z = 0;
	w = 0;
	while (z < info->rooms[path->root[i][k]]->links_len)
	{
		if (info->rooms[path->root[i][k]]->links[z] != path->root[i][k - 1] &&
			info->rooms[path->root[i][k]]->links[z] != path->root[i][k + 1])
		{
			info->time[path->root[i][k]]->links[w++] =
				info->rooms[path->root[i][k]]->links[z];
			!info->time[info->rooms[path->root[i][k]]->links[z]] ? perdoz(info,
info->rooms[path->root[i][k]]->links[z], path->root[i][k], v) :
perdoz_2(info, info->rooms[path->root[i][k]]->links[z], path->root[i][k], v);
		}
		z++;
	}
	return (w);
}

void				delite(t_info *info, t_path *path)
{
	int				i;
	int				k;
	int				w;
	int				v;

	init_time(info, path);
	v = info->count_room;
	i = 0;
	while (i < path->count_root)
	{
		k = 1;
		while (k < path->len_root[i] - 1)
		{
			init_v(info, v, path->root[i][k]);
			info->time[v]->links[0] = path->root[i][k - 1];
			w = delite_prt1(info, path, i * 1000000 + k, v);
			info->time[path->root[i][k]]->links[w] = v;
			v++;
			k++;
		}
		i++;
	}
	init_start(info, path);
	fill_rest(info);
}
