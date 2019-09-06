/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:54:36 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/06 19:54:39 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

int					do_path_part_1(t_info *info, t_path **path)
{
	init_path0(path);
	weight(info);
	if (info->len_path[info->end] == 1000000)
		return (-1);
	init_path0_continue(info, path);
	build_path(info, path[0], info->end, 1);
	do_count(info, path[0]);
	vibor_krotchaishego(info, path[0]);
	return (1);
}

void				do_path_part_2(t_info *info, t_path **path, int i)
{
	delite(info, path[i - 1]);
	init_path_i(path, i);
	weight_den(info);
}

void				do_path_part_3(t_info *info, t_path **path, int i)
{
	build_path_den(info->path, path[i], info);
	copy_prepath(path, i);
	rebuild_path(path, i);
	do_count(info, path[i]);
}

void				free_path0(t_path **path, t_info *info)
{
	free(path[0]);
	free(path[0]->root);
	free(path[0]->len_root);
	free(path);
	free(info->len_path);
}

int					do_path(t_info *info)
{
	t_path		**path;
	int			i;
	int			rex;

	rex = 1;
	path = (t_path **)malloc(sizeof(t_path *) *
		info->rooms[info->start]->links_len);
	if (do_path_part_1(info, path) == -1)
	{
		free_path0(path, info);
		return (-1);
	}
	i = 1;
	while (i < info->rooms[info->start]->links_len && rex)
	{
		do_path_part_2(info, path, i);
		if (info->len_path[info->end] == 1000000)
			rex = 0;
		else
		{
			do_path_part_3(info, path, i);
			if (path[i]->itog <= info->count_string && path[i]->check)
				vibor_krotchaishego(info, path[i]);
			else
				rex = 0;
		}
		clean_del(info);
		i++;
	}
	free_pathes(info, path, i);
	return (1);
}