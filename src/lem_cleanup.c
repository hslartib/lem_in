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

#include "./inc/lem_strt.h"

void	cleanup_room(t_room *room)
{
	free(room->name);
	free(room->links);
	free(room->all_path);
	free(room);
}

void	cleanup_info(t_info *info)
{
	int r;

	r = -1;
	free(info->len_path);
	while (++r < info->count_room)
		cleanup_room(info->rooms[r]);
	free(info->rooms);
	free(info);
}