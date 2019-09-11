/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 03:17:40 by dbrady            #+#    #+#             */
/*   Updated: 2019/08/15 03:17:42 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

void	cleanup_room(t_room *room)
{
	if (room->name)
		free(room->name);
	if (room->links)
		free(room->links);
	if (room->all_path)
		free(room->all_path);
	free(room);
}

void	cleanup_info(t_info *info)
{
	int r;

	r = -1;
	if (info)
	{
		if (info->rooms)
		{
			while (++r < info->count_room)
				if (info->rooms[r])
					cleanup_room(info->rooms[r]);
			free(info->rooms);
		}
		if (info->input)
			ft_strdel_2d(&info->input);
		free(info);
	}
}
