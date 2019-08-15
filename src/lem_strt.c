/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_strt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 12:37:57 by hslartib          #+#    #+#             */
/*   Updated: 2019/08/13 12:38:00 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/lem_strt.h"


//void len_vrtc(t_info *info, int index)
//{
//	int k;
//
//	k = 0;
//	while (k < info->rooms[index]->links_len && (info->len_path[info->rooms[index]->links[k]] == 0 || info->len_path[index] + 1 < info->len_path[info->rooms[index]->links[k]]) && k != info->start)
//	{
//		info->len_path[k] = info->len_path[index] + 1;
//		k++;
//	}
//	k = 0;
//	while (k < info->rooms[index]->links_len && info->len_path[k] == 0 && k != info->start)
//	{
//		len_vrtc(info, k);
//		k++;
//	}
//}
//
//void path(t_info *info, char *str, int index)
//{
//	int k;
//
//	k = 0;
//	while (k < info->rooms[index]->links_len && (info->len_path[index] + 1 = info->len_path[info->rooms[index]->links[0]] || info->len_path[k] = 0))
//	{
//		info->len_path[k] =
//		path(info, str, k);
//		k++;
//	}
//}
//
//void workroom(t_info *info)
//{
//	int		i;
//	char	*str;
//
//	str = ft_strnew(0);
//	info->len_path = (int *)malloc(sizeof(int) * info->count_room);
//	i = 0;
//	while (i < info->count_room)
//		info->len_path[i++] = 0;
//	len_vrtc(info, info->start);
//	path(info, str, info->start);
//}

int main()
{
	t_info *info;

	if (!(info = (t_info *)malloc(sizeof(t_info))))
		return (0);
	info_init(info);
//	workroom(info);
	cleanup_info(info);
	return (0);
}
