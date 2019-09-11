/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_double_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:09:09 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/06 20:09:12 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

void				copy_first(int *src, int *dep, int count)
{
	int				i;

	i = 0;
	while (i < count)
	{
		dep[i] = src[i];
		i++;
	}
}

void				copy_last(int *src, int *dep, int last_s, int last_d)
{
	int				i;

	i = 0;
	while (i <= last_d && i <= last_s)
	{
		dep[last_d - i] = src[last_s - i];
		i++;
	}
}

void				do_pos(t_path *path, int index, int r, t_pos *pos)
{
	int				x;
	int				i;
	int				k;

	x = 0;
	i = 0;
	while (i < path->len_root[index])
	{
		k = 0;
		while (k < path->len_root[r])
		{
			if (path->root[index][i] == path->root[r][k] &&
				i != 0 && i != path->len_root[index] - 1)
			{
				pos->pos1[x] = i;
				pos->pos2[x] = k;
				x = 1;
			}
			k++;
		}
		i++;
	}
}

void				init_pos(t_pos *pos)
{
	pos->pos1[0] = 0;
	pos->pos1[1] = 0;
	pos->pos2[0] = 0;
	pos->pos2[1] = 0;
}
