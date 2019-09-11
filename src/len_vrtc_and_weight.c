/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_vrtc_and_weight.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:56:58 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/06 19:57:00 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

void				len_vrtc(t_info *info, int nbr)
{
	int			k;
	int			i;

	i = 0;
	while (i < info->count_room)
	{
		if (info->len_path[i] == nbr)
		{
			k = 0;
			while (k < info->rooms[i]->links_len)
			{
				if (info->len_path[info->rooms[i]->links[k]]
					> info->len_path[i] + 1)
					info->len_path[info->rooms[i]->links[k]] =
						info->len_path[i] + 1;
				k++;
			}
		}
		i++;
	}
	if (!check_len(info, nbr + 1))
		len_vrtc(info, nbr + 1);
}

void				weight(t_info *info)
{
	int			i;

	info->len_path = (int *)malloc(sizeof(int) * info->count_room);
	i = 0;
	while (i < info->count_room)
		info->len_path[i++] = 1000000;
	info->len_path[info->start] = 0;
	i = 0;
	while (i < info->rooms[info->start]->links_len)
	{
		info->len_path[info->rooms[info->start]->links[i]] = 1;
		i++;
	}
	if (!check_len(info, 1))
		len_vrtc(info, 1);
}
