/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:51:39 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/06 19:51:43 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

int					help_build(t_path *path, t_info *info, char **mas)
{
	int			i;
	int			len;

	len = 0;
	while (mas[len])
		len++;
	path->len_root[path->count_root - 1] = len;
	path->root[path->count_root - 1] = (int *)malloc(sizeof(int) * len);
	i = 0;
	len = 0;
	while (mas[i])
	{
		path->root[path->count_root - 1][i] = ft_atoi(mas[i]);
		free(mas[i]);
		if (path->root[path->count_root - 1][i] >= info->count_room)
			path->root[path->count_root - 1][i] =
				info->time[path->root[path->count_root - 1][i]]->true_index;
		if (i > 0 && path->root[path->count_root - 1][i] ==
			path->root[path->count_root - 1][i - 1])
			len++;
		i++;
	}
	return (len);
}

void				build_path_den(char *str, t_path *path, t_info *info)
{
	int			i;
	int			len;
	int			z;
	int			*op;
	char		**mas;

	mas = ft_strsplit(str, '-');
	len = help_build(path, info, mas);
	free(str);
	op = path->root[path->count_root - 1];
	path->len_root[path->count_root - 1] -= len;
	path->root[path->count_root - 1] = (int *)malloc(sizeof(int) *
		path->len_root[path->count_root - 1]);
	i = 0;
	z = 0;
	while (i < path->len_root[path->count_root - 1] + len)
	{
		if (i == 0)
			path->root[path->count_root - 1][z++] = op[i];
		else if (i > 0 && op[i] != op[i - 1])
			path->root[path->count_root - 1][z++] = op[i];
		i++;
	}
	free(mas);
	free(op);
}

void				rebuild_path(t_path **path, int index)
{
	int			k;
	int			z;

	z = path[index]->count_root - 1;
	while (z >= 0)
	{
		k = z - 1;
		while (k >= 0)
		{
			double_path(path[index], z, k);
			k--;
		}
		z--;
	}
}

void				build_path(t_info *info, t_path *path, int index, int lamp)
{
	int			k;
	int			l;

	k = 0;
	path->root[path->count_root - 1][path->score--] = index;
	while (k < info->rooms[index]->links_len && index != info->start)
	{
		if (info->len_path[index] - 1 ==
			info->len_path[info->rooms[index]->links[k]] && lamp && !path->check)
		{
			l = path->score;
			build_path(info, path, info->rooms[index]->links[k], 1);
			!path->check ? path->score = l : 0;
		}
		k++;
	}
	index == info->end ? free(info->len_path) : 0;
}
