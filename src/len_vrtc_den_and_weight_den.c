/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_vrtc_den_and_weight_den.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:56:31 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/06 19:56:33 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

char				*obsilut_str(char *str, int index)
{
	char		*lari;
	char		*dodo;
	char		*namnam;

	lari = ft_strjoin(str, "-");
	namnam = ft_itoa(index);
	dodo = ft_strjoin(lari, namnam);
	free(lari);
	free(namnam);
	return (dodo);
}

char				*help_str_vrtc(char *str, int index, t_info *info)
{
	char		*dodo;

	dodo = obsilut_str(str, index);
	if (index == info->end)
	{
		if (info->cou_d == 1000000)
		{
			info->cou_d = info->len_path[info->end];
			info->path = dodo;
		}
		else if (info->len_path[info->end] < info->cou_d)
		{
			info->cou_d = info->len_path[info->end];
			free(info->path);
			info->path = dodo;
		}
		else
			free(dodo);
	}
	return (dodo);
}

void				len_vrtc_den(t_info *info, int index, char *str)
{
	int			k;

	str = help_str_vrtc(str, index, info);
	k = 0;
	while (k < info->time[index]->links_len && index != info->end)
	{
		if (info->time[index]->rebuild == -1 &&
			info->len_path[info->time[index]->links[k]] > info->len_path[index] - 1)
			vrtc_den_1(info, index, str, k);
		else if ((info->time[index]->rebuild == 1 ||
			!info->time[index]->rebuild) &&
			info->len_path[info->time[index]->links[k]] > info->len_path[index] + 1)
			vrtc_den_2(info, index, str, k);
		else if (info->time[index]->rebuild == 10)
		{
			if (info->time[info->time[index]->links[k]]->rebuild == -1 &&
				info->len_path[info->time[index]->links[k]] > info->len_path[index])
				vrtc_den_3(info, index, str, k);
			else if (info->time[info->time[index]->links[k]]->rebuild != -1 &&
				info->len_path[info->time[index]->links[k]] > info->len_path[index] + 1)
				vrtc_den_4(info, index, str, k);
		}
		k++;
	}
	index != info->end ? free(str) : 0;
}

void				weight_den(t_info *info)
{
	int			i;
	char		*str;

	i = 0;
	info->cou_d = 1000000;
	info->len_path = (int *)malloc(sizeof(int) * (info->count_time));
	while (i < info->count_time)
		info->len_path[i++] = 1000000;
	info->len_path[info->start] = 0;
	i = 0;
	str = ft_itoa(info->start);
	while (i < info->time[info->start]->links_len)
	{
		info->len_path[info->time[info->start]->links[i]] = 1;
		len_vrtc_den(info, info->time[info->start]->links[i], str);
		i++;
	}
	free(str);
	free(info->len_path);
}