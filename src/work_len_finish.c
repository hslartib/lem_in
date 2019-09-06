/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_len_finish.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 17:49:53 by hslartib          #+#    #+#             */
/*   Updated: 2019/08/14 17:49:54 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

//void		len_vrt_end(t_info *info, t_end *end, int index)
//{
//	int k;
//
//	k = 0;
//	while (k < info->rooms[index]->links_len)
//	{
//		if ((end->len_path[info->rooms[index]->links[k]] == 0 || end->len_path[index] + 1 < end->len_path[info->rooms[index]->links[k]]) && info->rooms[index]->links[k] != info->end)
//		{
//			end->len_path[info->rooms[index]->links[k]] = end->len_path[index] + 1;
//			len_vrt_end(info, end, info->rooms[index]->links[k]);
//		}
//		k++;
//	}
//}
//
//void 		end_path(t_info *info, t_end *end, char *str, int main, int index)
//{
//	int k;
//	char **path_indx;
//	char *tmp;
//
//	printf("%d - %d\n", main, index);
//	path_indx = info->rooms[main]->end_path;
//	k = 0;
//	tmp = ft_strjoin("-", ft_itoa(index));
//	str = ft_strjoin(str, tmp);
//	if (!double_end_path(info->rooms[main], str) && index == info->end)
//	{
//		path_indx[info->rooms[main]->count_end] = str;
//		info->rooms[main]->count_end++;
//	}
//	while (k < info->rooms[index]->links_len)
//	{
//		if (end->len_path[index] >= end->len_path[info->rooms[index]->links[k]] && !check_end(str, info->rooms[index]->links[k]) && index != info->end && info->rooms[index]->links[k] != main)
//			end_path(info, end, str, main, info->rooms[index]->links[k]);
//		k++;
//	}
//
//}
//
//void sasha(t_info *info, t_end *end)
//{
//	int k;
//	int i;
//	char	*str;
//	int		index;
//
//	str = ft_strnew(0);
//	k = 0;
//	i = 0;
//	while (i < info->count_end_vrt)
//	{
//		k = 0;
//		index = info->vrtc_end[i];
//		while (k < info->rooms[index]->links_len)
//		{
//			printf("HOHOH %d - %d\n", k, info->rooms[index]->links[k]);
//			if (end->len_path[index] >= end->len_path[info->rooms[index]->links[k]])
//				end_path(info, end, str, index, info->rooms[index]->links[k]);
//			k++;
//		}
//		int z = 0;
//		while (z < info->rooms[index]->count_end)
//		{
//			printf("%d -|- %s\n", index, info->rooms[index]->end_path[z]);
//			z++;
//		}
//
//		i++;
//	}
//
//
//
//
//
//
//}
//
//
//void		work_len_finish(t_info *info, t_end *end)
//{
//	int i;
//	char *str;
//
//	end->count_room = info->count_room;
//	end->len_path = (int *)malloc(sizeof(int) * end->count_room);
//	i = 0;
//	while (i < info->count_room)
//		info->len_path[i++] = 0;
//	len_vrt_end(info, end, info->end);
//
//
//	str = ft_strnew(0);
//	i = 0;
//	while (i < info->count_end_vrt)
//	{
//		info->rooms[info->vrtc_end[i]]->end_path = (char **)malloc(sizeof(char *) * 1000);
//		ft_bzero(info->rooms[info->vrtc_end[i]]->end_path, sizeof(char *) * 1000);
//		info->rooms[info->vrtc_end[i]]->count_end = 0;
//
//		i++;
//	}
//	sasha(info, end);
//
//}
