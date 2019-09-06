/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 11:46:14 by hslartib          #+#    #+#             */
/*   Updated: 2019/08/15 11:46:16 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

void				clean_del(t_info *info)
{
	int				i;

	i = 0;
	while (i < info->count_time)
	{
		if (info->time[i]->rebuild == 0)
		{
		}
		else if (info->time[i]->rebuild == 1 ||
		info->time[i]->rebuild == -1 || info->time[i]->rebuild == 10)
		{
			free(info->time[i]->links);
			free(info->time[i]);
		}
		i++;
	}
	free(info->time);
}

void				free_pathes(t_info *info, t_path **path, int count)
{
	int				i;
	int				k;

	i = 0;
	while (i < count)
	{
		if (path[i] != info->marshroot)
		{
			k = 0;
			while (k < path[i]->count_root)
			{
				free(path[i]->root[k]);
				k++;
			}
			free(path[i]->len_root);
			free(path[i]->root);
			free(path[i]->count_ant);
			free(path[i]);
		}
		i++;
	}
	free(path);
}
