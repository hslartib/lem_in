/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:09:46 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/06 20:09:48 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

void				double_path_do_prt1(t_path *path, int index, int *mas1)
{
	int				*a;

	a = path->root[index];
	path->root[index] = mas1;
	free(a);
}

void				double_path_do1(t_path *path, int index, int r, t_pos *pos)
{
	int				*mas1;
	int				*mas2;
	int				l;

	mas1 = (int *)malloc(sizeof(int) *
		(pos->pos1[0] + 1 + path->len_root[r] - (pos->pos2[0] + 1)));
	mas2 = (int *)malloc(sizeof(int) *
		(pos->pos2[1] + 1 + path->len_root[index] - (pos->pos1[1] + 1)));
	copy_last(path->root[r], mas1, path->len_root[r] - 1,
			  pos->pos1[0] + 1 + path->len_root[r] - (pos->pos2[0] + 1) - 1);
	copy_first(path->root[index], mas1, pos->pos1[0] + 1);
	copy_last(path->root[index], mas2, path->len_root[index] - 1,
			  pos->pos2[1] + 1 + path->len_root[index] - (pos->pos1[1] + 1) - 1);
	copy_first(path->root[r], mas2, pos->pos2[1] + 1);
	double_path_do_prt1(path, index, mas1);
	double_path_do_prt1(path, r, mas2);
	l = pos->pos2[1] + 1 + path->len_root[index]
		- (pos->pos1[1] + 1);
	path->len_root[index] = pos->pos1[0] + 1 +
		path->len_root[r] - (pos->pos2[0] + 1);
	path->len_root[r] = l;
}

void				double_path(t_path *path, int index, int r)
{
	t_pos			*pos;

	pos = (t_pos *)malloc(sizeof(t_pos));
	init_pos(pos);
	do_pos(path, index, r, pos);
	if (pos->pos1[0] < pos->pos1[1])
	{
		double_path_do1(path, index, r, pos);
		free(pos);
		return ;
	}
	free(pos);
}
