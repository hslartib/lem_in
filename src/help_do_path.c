/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_do_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:55:09 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/06 19:55:12 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

void				init_path0(t_path **path)
{
	path[0] = (t_path *)malloc(sizeof(t_path));
	path[0]->root = (int **)malloc(sizeof(int *));
	path[0]->len_root = (int *)malloc(sizeof(int));
	path[0]->count_root = 1;
	path[0]->check = 0;
}

void				init_path0_continue(t_info *info, t_path **path)
{
	path[0]->len_root[0] = info->len_path[info->end] + 1;
	path[0]->root[0] = (int *)malloc(sizeof(int) * path[0]->len_root[0]);
	path[0]->score = path[0]->len_root[0] - 1;
}

void				vibor_krotchaishego(t_info *info, t_path *path)
{
	info->marshroot = path;
	info->count_string = path->itog;
}

void				init_path_i(t_path **path, int i)
{
	path[i] = (t_path *)malloc(sizeof(t_path));
	path[i]->root = (int **)malloc(sizeof(int *) * (i + 1));
	path[i]->len_root = (int *)malloc(sizeof(int) * (i + 1));
	path[i]->count_root = i + 1;
}
