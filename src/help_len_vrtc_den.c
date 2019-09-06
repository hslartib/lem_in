/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_len_vrtc_den.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:54:58 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/06 19:55:01 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

void				vrtc_den_1(t_info *info, int index, char *str, int k)
{
	info->len_path[info->time[index]->links[k]] = info->len_path[index] - 1;
	len_vrtc_den(info, info->time[index]->links[k], str);
}

void				vrtc_den_2(t_info *info, int index, char *str, int k)
{
	info->len_path[info->time[index]->links[k]] = info->len_path[index] + 1;
	len_vrtc_den(info, info->time[index]->links[k], str);
}

void				vrtc_den_3(t_info *info, int index, char *str, int k)
{
	info->len_path[info->time[index]->links[k]] = info->len_path[index];
	len_vrtc_den(info, info->time[index]->links[k], str);
}

void				vrtc_den_4(t_info *info, int index, char *str, int k)
{
	info->len_path[info->time[index]->links[k]] = info->len_path[index] + 1;
	len_vrtc_den(info, info->time[index]->links[k], str);
}