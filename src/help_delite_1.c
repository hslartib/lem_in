/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_delite_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:11:14 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/06 20:11:17 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

int					check_len(t_info *info, int nbr)
{
	int				i;

	i = 0;
	while (i < info->count_room)
	{
		if (nbr == info->len_path[i])
			return (0);
		i++;
	}
	return (-1);
}

void				copy_prepath(t_path **path, int index)
{
	int				i;
	int				k;

	i = 0;
	while (i < path[index - 1]->count_root)
	{
		k = 0;
		path[index]->root[i] = (int *)malloc(sizeof(int)
												 * path[index - 1]->len_root[i]);
		path[index]->len_root[i] = path[index - 1]->len_root[i];
		while (k < path[index - 1]->len_root[i])
		{
			path[index]->root[i][k] = path[index - 1]->root[i][k];
			k++;
		}
		i++;
	}
}

void				perdoz(t_info *info, int src, int out, int in)
{
	int				i;

	if (!info->time[src])
	{
		info->time[src] = (t_room *)malloc(sizeof(t_room));
		info->time[src]->links_len = info->rooms[src]->links_len;
		info->time[src]->links = (int *)malloc(sizeof(int)
												   * info->time[src]->links_len);
		info->time[src]->index = src;
		info->time[src]->rebuild = 1;
	}
	i = 0;
	while (i < info->time[src]->links_len)
	{
		if (info->rooms[src]->links[i] == out)
			info->time[src]->links[i] = in;
		else
			info->time[src]->links[i] = info->rooms[src]->links[i];
		i++;
	}
}

void				perdoz_2(t_info *info, int src, int out, int in)
{
	int				i;

	i = 0;
	while (i < info->time[src]->links_len)
	{
		if (info->rooms[src]->links[i] == out)
		{
			info->time[src]->links[i] = in;
			return ;
		}
		i++;
	}
}

int					check_start_time(int dep, t_path *path)
{
	int				i;

	i = 0;
	while (i < path->count_root)
	{
		if (dep == path->root[i][1])
			return (0);
		i++;
	}
	return (1);
}