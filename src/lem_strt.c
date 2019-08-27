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

#include "lem_strt.h"

//void	end_vertc(t_info *info, char *str)
//{
//	int i;
//	char **mas;
//
//	mas = ft_strsplit(str, '-');
//	i = 0;
//	while (mas[i])
//		i++;
//	info->count_end_vrt = i;
//	info->vrtc_end = (int *)malloc(sizeof(int) * i);
//	i = 0;
//	while (mas[i])
//	{
//		info->vrtc_end[i] = ft_atoi(mas[i]);
//		free(mas[i]);
//		i++;
//	}
//	free(mas);
//	free(str);
//}

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
//		len_vrtc(info, info->rooms[index]->links[k]);
//		k++;
//	}
//}
//
//void path(t_info *info, char *str, int index, char **vrtc_end)
//{
//	int k;
//	int i;
//	char *path_indx;
//
//	path_indx = info->rooms[index]->all_path;
//	k = 0;
//	i = 0;
//	if (*str)
//		str = ft_strjoin("-", str);
//	str = ft_strjoin(str, ft_itoa(index));
//	if (index != info->start && !(ft_strstr(path_indx, str)))
//	{
//		if (*str)
//			str = ft_strjoin("#", str);
//		path_indx = ft_strjoin(path_indx, str);
//	}
//	while (k < info->rooms[index]->links_len)
//	{
//		if (info->len_path[index] + 1 == info->len_path[info->rooms[index]->links[k]])
//		{
//			path(info, str, k);
//			i++;
//		}
//		k++;
//	}
//	if (!i)
//	{
//		if (**vrtc_end)
//			*vrtc_end = ft_strjoin("-", *vrtc_end);
//		*vrtc_end = ft_strjoin(*vrtc_end, ft_itoa(index));
//	}
//}
//
//void workroom(t_info *info)
//{
//	int		i;
//	char	*str;
//	char	*vrtc_end;
//
//	str = ft_strnew(0);
//	vrtc_end = ft_strnew(0);
//
//	info->len_path = (int *)malloc(sizeof(int) * info->count_room);
//	i = 0;
//	while (i < info->count_room)
//		info->len_path[i++] = 0;
//	len_vrtc(info, info->start);
//	path(info, str, info->start, &vrtc_end);
//	end_vertc(info, vrtc_end);
//}

int main()
{
	t_info *info;

	if (!(info = (t_info *)malloc(sizeof(t_info))))
		return (0);
	if (info_init(info) != ALLRIGHT) {
		printf("test says: \"Error!\"\n");
		return (0);
	}
	else
		printf("test says: \"Allright!\"\n");
	printf("rooms: %d\n", info->count_room);
	lem_sdl_control(info);
//	workroom(info);
//	cleanup_info(info);
//	workroom(info);
//	work_len_finish(info);
	return (0);
}
