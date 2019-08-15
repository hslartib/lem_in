/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_len_finish.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:49:53 by hslartib          #+#    #+#             */
/*   Updated: 2019/08/14 17:49:54 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

void		len_vrt_end(t_info *info, t_end *end, int index)
{
	int k;

	k = 0;
	while (k < info->rooms[index]->links_len)
	{
		if ((info->len_path[info->rooms[index]->links[k]] == 0 || info->len_path[index] + 1 < info->len_path[info->rooms[index]->links[k]]) && k != info->start)
			end->len_path[info->rooms[index]->links[k]] = end->len_path[index] + 1;
		k++;
	}
	k = 0;
	while (k < info->rooms[index]->links_len && info->len_path[k] == 0 && k != info->start)
	{
		len_vrt_end(info, end, info->rooms[index]->links[k]);
		k++;
	}
}

void		work_len_finish(t_info *info, t_end *end)
{
	int i;

	info->len_path = (int *)malloc(sizeof(int) * info->count_room);
	i = 0;
	while (i < info->count_room)
		info->len_path[i++] = 0;
	len_vrt_end(info, info->start, info->end);
}
