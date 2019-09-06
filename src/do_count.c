/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:54:25 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/06 19:54:30 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

int					find_max(t_path *path)
{
	int			i;
	int			max;

	max = 0;
	i = 0;
	while (i < path->count_root)
	{
		if (path->len_root[i] - 1 > max)
			max = path->len_root[i] - 1;
		i++;
	}
	return (max);
}

int					find_len(t_path *path, t_info *info, int max)
{
	int			i;
	int			len;

	len = info->count_ants;
	i = 0;
	while (i < path->count_root)
	{
		len -= (max - (path->len_root[i] - 1));
		i++;
	}
	len /= path->count_root;
	return (len);
}

int					find_mod(t_path *path, t_info *info, int max, int len)
{
	int			mod;
	int			i;

	path->check = 1;
	mod = 0;
	i = 0;
	path->itog = 0;
	while (i < path->count_root)
	{
		path->count_ant[i] = len + (max - (path->len_root[i] - 1));
		if (path->count_ant[i] <= 0)
			path->check = 0;
		mod += path->count_ant[i];
		i++;
	}
	mod = info->count_ants - mod;
	return (mod);
}

void				bit(t_path *path, int mod)
{
	int			i;

	i = 0;
	while (i < mod)
	{
		path->count_ant[i]++;
		i++;
	}
}

void				do_count(t_info *info, t_path *path)
{
	int			i;
	int			max;
	int			len;
	int			mod;

	path->count_ant = (int *)malloc(sizeof(int) * path->count_root);
	max = find_max(path);
	len = find_len(path, info, max);
	mod = find_mod(path, info, max, len);
	bit(path, mod);
	i = 0;
	while (i < path->count_root)
	{
		if ((path->len_root[i] - 1 + (path->count_ant[i] - 1)) > path->itog)
			path->itog = path->len_root[i] - 1 + (path->count_ant[i] - 1);
		i++;
	}
}