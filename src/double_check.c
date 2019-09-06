/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 11:46:14 by hslartib          #+#    #+#             */
/*   Updated: 2019/08/15 11:46:16 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"


void copy_first(int *src, int *dep, int count)
{
	int i;


	i = 0;
	while (i < count)
	{
		dep[i] = src[i];
		i++;
	}
}


void copy_last(int *src, int *dep, int last_s, int last_d)
{
	int i;

	i = 0;
	while (i <= last_d && i <= last_s)
	{
		dep[last_d - i] = src[last_s - i];
		i++;
	}
}


typedef struct		s_pos
{
	int pos1[2];
	int pos2[2];
}					t_pos;



void do_pos(t_path *path, int index, int r, t_pos *pos)
{
	int x;
	int i;
	int k;


	x = 0;
	i = 0;
	while (i < path->len_root[index])
	{
		k = 0;

		while (k < path->len_root[r])
		{

			if (path->root[index][i] == path->root[r][k] && i != 0 && i != path->len_root[index] - 1)
			{
				if (!x)
				{
					pos->pos1[x] = i;
					pos->pos2[x++] = k;
				}
				else
				{
					pos->pos1[x] = i;
					pos->pos2[x] = k;
				}
			}
			k++;
		}
		i++;
	}
}



void init_pos(t_pos *pos)
{
	pos->pos1[0] = 0;
	pos->pos1[1] = 0;
	pos->pos2[0] = 0;
	pos->pos2[1] = 0;
}

void double_path_do1(t_path *path, int index, int r, t_pos *pos)
{
	int *mas1;
	int *mas2;
	int *a;
	int l;

	mas1 = (int *) malloc(sizeof(int) * (pos->pos1[0] + 1 + path->len_root[r] - (pos->pos2[0] + 1)));
	mas2 = (int *) malloc(sizeof(int) * (pos->pos2[1] + 1 + path->len_root[index] - (pos->pos1[1] + 1)));

	copy_last(path->root[r], mas1, path->len_root[r] - 1, pos->pos1[0] + 1 + path->len_root[r] - (pos->pos2[0] + 1) - 1);
	copy_first(path->root[index], mas1, pos->pos1[0] + 1);

	copy_last(path->root[index], mas2, path->len_root[index] - 1,	pos->pos2[1] + 1 + path->len_root[index] - (pos->pos1[1] + 1) - 1);
	copy_first(path->root[r], mas2, pos->pos2[1] + 1);

	a = path->root[index];
	path->root[index] = mas1;
	free(a);
	a = path->root[r];
	path->root[r] = mas2;
	free(a);
	l = pos->pos2[1] + 1 + path->len_root[index] - (pos->pos1[1] + 1);
	path->len_root[index] = pos->pos1[0] + 1 + path->len_root[r] - (pos->pos2[0] + 1);
	path->len_root[r] = l;
}










void	double_path(t_path *path, int index, int r)
{
	t_pos *pos;

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





















int check_len(t_info *info, int nbr)
{
	int i;

	i = 0;
	while (i < info->count_room)
	{
		if (nbr == info->len_path[i])
			return (0);
		i++;
	}
	return (-1);
}











void copy_prepath(t_path **path, int index)
{
	int i;
	int k;

	i = 0;
	while (i < path[index - 1]->count_root)
	{
		k = 0;
		path[index]->root[i] = (int *)malloc(sizeof(int) * path[index - 1]->len_root[i]);
		path[index]->len_root[i] =  path[index - 1]->len_root[i];
		while (k < path[index - 1]->len_root[i])
		{
			path[index]->root[i][k] = path[index - 1]->root[i][k];
			k++;
		}
		i++;
	}
}




















void perdoz(t_info *info, int src, int out, int in)
{
	int i;

	if (!info->time[src])
	{
		info->time[src] = (t_room *)malloc(sizeof(t_room));
		info->time[src]->links_len = info->rooms[src]->links_len;
		info->time[src]->links = (int *)malloc(sizeof(int) * info->time[src]->links_len);
		info->time[src]->index = src;
		info->time[src]->rebuild = 1;
	}

	i = 0;
	while (i < info->time[src]->links_len)
	{
		if (info->rooms[src]->links[i] == out)
			info->time[src]->links[i] = in;
		else
			info->time[src]->links[i] = info->rooms[src]->links[i];
		i++;
	}
}


void perdoz_2(t_info *info, int src, int out, int in)
{
	int i;

	i = 0;
	while (i < info->time[src]->links_len)
	{
		if (info->rooms[src]->links[i] == out)
		{
			info->time[src]->links[i] = in;
			return ;
		}
		i++;
	}
}



int check_start_time(int dep, t_path *path)
{
	int i;

	i = 0;
	while (i < path->count_root)
	{
		if (dep == path->root[i][1])
			return (0);
		i++;
	}
	return (1);
}










void room_in_time_copy(t_room *room, t_info *info, int index)
{
	info->time[index] = room;
	info->time[index]->rebuild = 0;
}


void fill_rest(t_info *info)
{
	int i;

	i = 0;
	while (i < info->count_time)
	{
		if (!info->time[i])
			room_in_time_copy(info->rooms[i], info, i);
		i++;
	}
}











//void init_time(t_info *info, t_path *path)
//{
//	int v;
//	int w;
//
//	w = 0;
//	info->count_time = 0;
//	while (w < path->count_root)
//	{
//		info->count_time += path->len_root[w];
//		w++;
//	}
//	info->count_time -= (w * 2);
//	info->count_time += info->count_room;
//	info->time = (t_room **)malloc(sizeof(t_room *) * info->count_time);
//	v = 0;
//	while (v < info->count_room)
//	{
//		info->time[v] = NULL;
//		v++;
//	}
//}
//
//
//
//void init_v(t_info *info, int v, int kl)
//{
//	info->time[v] = (t_room *)malloc(sizeof(t_room));
//	info->time[v]->index = v;
//	info->time[v]->links_len = 1;
//	info->time[v]->links = (int *)malloc(sizeof(int));
//	info->time[v]->rebuild = -1;
//	info->time[v]->true_index = kl;
//
//
//	info->time[kl] = (t_room *)malloc(sizeof(t_room));
//	info->time[kl]->index = kl;
//	info->time[kl]->links_len = info->rooms[kl]->links_len - 1;
//	info->time[kl]->links = (int *)malloc(sizeof(int) * info->time[kl]->links_len);
//	info->time[kl]->rebuild = 10;
//}
//
//void init_start(t_info *info, t_path *path)
//{
//	int z;
//	int w;
//
//	info->time[info->start] = (t_room *) malloc(sizeof(t_room));
//	info->time[info->start]->index = info->start;
//	info->time[info->start]->links_len = info->rooms[info->start]->links_len - path->count_root;
//	info->time[info->start]->links = (int *) malloc(sizeof(int) * info->time[info->start]->links_len);
//	info->time[info->start]->rebuild = 1;
//	w = 0;
//	z = 0;
//	while (z < info->rooms[info->start]->links_len)
//	{
//		if (check_start_time(info->rooms[info->start]->links[z], path))
//			info->time[info->start]->links[w++] = info->rooms[info->start]->links[z];
//		z++;
//	}
//}
//
//
//
//
//
//void delite(t_info *info, t_path *path)
//{
//	int i;
//	int k;
//	int w;
//	int v;
//	int z;
//
//	init_time(info, path);
//
//	v = info->count_room;
//	i = 0;
//	while (i < path->count_root)
//	{
//		k = 1;
//		while (k < path->len_root[i] - 1)
//		{
//			init_v(info, v, path->root[i][k]);
//			info->time[v]->links[0] = path->root[i][k - 1];
//
//			z = 0;
//			w = 0;
//			while (z < info->rooms[path->root[i][k]]->links_len)
//			{
//				if (info->rooms[path->root[i][k]]->links[z] != path->root[i][k - 1] && info->rooms[path->root[i][k]]->links[z] != path->root[i][k + 1])
//				{
//					info->time[path->root[i][k]]->links[w++] = info->rooms[path->root[i][k]]->links[z];
//					!info->time[info->rooms[path->root[i][k]]->links[z]] ? perdoz(info, info->rooms[path->root[i][k]]->links[z], path->root[i][k], v) : perdoz_2(info, info->rooms[path->root[i][k]]->links[z], path->root[i][k], v);
//				}
//				z++;
//			}
//			info->time[path->root[i][k]]->links[w] = v;
//			v++;
//			k++;
//		}
//		i++;
//	}
//	init_start(info, path);
//	fill_rest(info);
//}







void init_time(t_info *info, t_path *path)
{
	int v;
	int w;

	w = 0;
	info->count_time = 0;
	while (w < path->count_root)
	{
		info->count_time += path->len_root[w];
		w++;
	}
	info->count_time -= (w * 2);
	info->count_time += info->count_room;
	info->time = (t_room **)malloc(sizeof(t_room *) * info->count_time);
	v = 0;
	while (v < info->count_room)
	{
		info->time[v] = NULL;
		v++;
	}
}



void init_v(t_info *info, int v, int kl)
{
	info->time[v] = (t_room *)malloc(sizeof(t_room));
	info->time[v]->index = v;
	info->time[v]->links_len = 1;
	info->time[v]->links = (int *)malloc(sizeof(int));
	info->time[v]->rebuild = -1;
	info->time[v]->true_index = kl;


	if (info->time[kl] == NULL)
		info->time[kl] = (t_room *)malloc(sizeof(t_room));
	else
	{
		free(info->time[kl]->links);
		free(info->time[kl]);
		info->time[kl] = (t_room *)malloc(sizeof(t_room));
	}
	info->time[kl]->index = kl;
	info->time[kl]->links_len = info->rooms[kl]->links_len - 1;
	info->time[kl]->links = (int *)malloc(sizeof(int) * info->time[kl]->links_len);
	info->time[kl]->rebuild = 10;
}

void init_start(t_info *info, t_path *path)
{
	int z;
	int w;

	info->time[info->start] = (t_room *) malloc(sizeof(t_room));
	info->time[info->start]->index = info->start;
	info->time[info->start]->links_len = info->rooms[info->start]->links_len - path->count_root;
	info->time[info->start]->links = (int *) malloc(sizeof(int) * info->time[info->start]->links_len);
	info->time[info->start]->rebuild = 1;
	w = 0;
	z = 0;
	while (z < info->rooms[info->start]->links_len)
	{
		if (check_start_time(info->rooms[info->start]->links[z], path))
			info->time[info->start]->links[w++] = info->rooms[info->start]->links[z];
		z++;
	}
}





void delite(t_info *info, t_path *path)
{
	int i;
	int k;
	int w;
	int v;
	int z;

	init_time(info, path);

	v = info->count_room;
	i = 0;
	while (i < path->count_root)
	{
		k = 1;
		while (k < path->len_root[i] - 1)
		{
			init_v(info, v, path->root[i][k]);
			info->time[v]->links[0] = path->root[i][k - 1];

			z = 0;
			w = 0;
			while (z < info->rooms[path->root[i][k]]->links_len)
			{
				if (info->rooms[path->root[i][k]]->links[z] != path->root[i][k - 1] && info->rooms[path->root[i][k]]->links[z] != path->root[i][k + 1])
				{
					info->time[path->root[i][k]]->links[w++] = info->rooms[path->root[i][k]]->links[z];
					!info->time[info->rooms[path->root[i][k]]->links[z]] ? perdoz(info, info->rooms[path->root[i][k]]->links[z], path->root[i][k], v) : perdoz_2(info, info->rooms[path->root[i][k]]->links[z], path->root[i][k], v);
				}
				z++;
			}
			info->time[path->root[i][k]]->links[w] = v;
			v++;
			k++;
		}
		i++;
	}
	init_start(info, path);
	fill_rest(info);
}




































//void clean_del(t_info *info, t_path *path)
//{
//    int i;
//    int k;
//    int w;
////	int v;
//
//    w = 0;
//    i = 0;
//    free(info->denied_link_start);
//    info->count_den_link = 0;
//    while (i < path->count_root)
//    {
////        info->denied_link_start[w++] = path->root[i][1];
////        info->rooms[path->root[i][1]]->only_link =  info->start;
////        info->count_den_link++;
//
////		printf("denied - %d\n", path->root[i][1]);
//
//        k = 2;
//        while (k < path->len_root[i])
//        {
//            info->rooms[path->root[i][k - 1]]->divide_index = 0;
//            info->rooms[path->root[i][k - 1]]->denied_link = -1;
//            info->rooms[path->root[i][k]]->only_link =  -1;
////			v = 0;
////			while (v < info->rooms[path->root[i][k]]->links_len)
////			{
////				if (info->rooms[path->root[i][k]]->links[v] == path->root[i][k - 1])
////					info->rooms[path->root[i][k]]->weight[v] = -1;
////			}
//
//
////			printf("denied - %d\n", path->root[i][k]);
//
//
//            k++;
//        }
//        i++;
//    }
//}






//void init_time(t_info *info, t_path *path)
//{
//	int v;
//	int w;
//
//	w = 0;
//	info->count_time = 0;
//	while (w < path->count_root)
//	{
//		info->count_time += path->len_root[w];
//		w++;
//	}
//	info->count_time -= (w * 2);
//	info->count_time += info->count_room;
//	info->time = (t_room **)malloc(sizeof(t_room *) * info->count_time);
//	v = 0;
//	while (v < info->count_room)
//	{
//		info->time[v] = NULL;
//		v++;
//	}
//}
//
//
//
//void init_v(t_info *info, int v, int kl)
//{
//	info->time[v] = (t_room *)malloc(sizeof(t_room));
//	info->time[v]->index = v;
//	info->time[v]->links_len = 1;
//	info->time[v]->links = (int *)malloc(sizeof(int));
//	info->time[v]->rebuild = -1;
//	info->time[v]->true_index = kl;
//
//
////	info->time[kl] = (t_room *)malloc(sizeof(t_room));
////	info->time[kl]->index = kl;
////	info->time[kl]->links_len = info->rooms[kl]->links_len - 1;
////	info->time[kl]->links = (int *)malloc(sizeof(int) * info->time[kl]->links_len);
////	info->time[kl]->rebuild = 10;
//}
//
//void init_start(t_info *info, t_path *path)
//{
//	int z;
//	int w;
//
//	info->time[info->start] = (t_room *) malloc(sizeof(t_room));
//	info->time[info->start]->index = info->start;
//	info->time[info->start]->links_len = info->rooms[info->start]->links_len - path->count_root;
//	info->time[info->start]->links = (int *) malloc(sizeof(int) * info->time[info->start]->links_len);
//	info->time[info->start]->rebuild = 1;
//	w = 0;
//	z = 0;
//	while (z < info->rooms[info->start]->links_len)
//	{
//		if (check_start_time(info->rooms[info->start]->links[z], path))
//			info->time[info->start]->links[w++] = info->rooms[info->start]->links[z];
//		z++;
//	}
//}
//
//
//
//
//
//void delite(t_info *info, t_path *path)
//{
//	int i;
//	int k;
//	int w;
//	int v;
//	int z;
//
//	init_time(info, path);
//
//	v = info->count_room;
//	i = 0;
//	while (i < path->count_root)
//	{
//		k = 1;
//		while (k < path->len_root[i] - 1)
//		{
//			init_v(info, v, path->root[i][k]);
//
//
//			info->time[path->root[i][k]] = (t_room *)malloc(sizeof(t_room));
//			info->time[path->root[i][k]]->index = path->root[i][k];
//			info->time[path->root[i][k]]->links_len = info->rooms[path->root[i][k]]->links_len - 1;
//			info->time[path->root[i][k]]->links = (int *)malloc(sizeof(int) * info->time[path->root[i][k]]->links_len);
//			info->time[path->root[i][k]]->rebuild = 10;
//
//
//
//
//
//
//			info->time[v]->links[0] = path->root[i][k - 1];
//
//			z = 0;
//			w = 0;
//			while (z < info->rooms[path->root[i][k]]->links_len)
//			{
//				if (info->rooms[path->root[i][k]]->links[z] != path->root[i][k - 1] && info->rooms[path->root[i][k]]->links[z] != path->root[i][k + 1])
//				{
//					info->time[path->root[i][k]]->links[w++] = info->rooms[path->root[i][k]]->links[z];
////					!info->time[info->rooms[path->root[i][k]]->links[z]] ? perdoz(info, info->rooms[path->root[i][k]]->links[z], path->root[i][k], v) : perdoz_2(info, info->rooms[path->root[i][k]]->links[z], path->root[i][k], v);
//				}
//				z++;
//			}
//			info->time[path->root[i][k]]->links[w] = v;
//			v++;
//			k++;
//		}
//		i++;
//	}
//
//	v = info->count_room;
//	i = 0;
//	while (i < path->count_root)
//	{
//		k = 1;
//		while (k < path->len_root[i] - 1)
//		{
////			init_v(info, v, path->root[i][k]);
////
////
////			info->time[path->root[i][k]] = (t_room *)malloc(sizeof(t_room));
////			info->time[path->root[i][k]]->index = path->root[i][k];
////			info->time[path->root[i][k]]->links_len = info->rooms[path->root[i][k]]->links_len - 1;
////			info->time[path->root[i][k]]->links = (int *)malloc(sizeof(int) * info->time[path->root[i][k]]->links_len);
////			info->time[path->root[i][k]]->rebuild = 10;
//
//
//
//
//
//
////			info->time[v]->links[0] = path->root[i][k - 1];
//
//			z = 0;
//			w = 0;
//			while (z < info->rooms[path->root[i][k]]->links_len)
//			{
//				if (info->rooms[path->root[i][k]]->links[z] != path->root[i][k - 1] && info->rooms[path->root[i][k]]->links[z] != path->root[i][k + 1])
//				{
////					info->time[path->root[i][k]]->links[w++] = info->rooms[path->root[i][k]]->links[z];
//					!info->time[info->rooms[path->root[i][k]]->links[z]] ? perdoz(info, info->rooms[path->root[i][k]]->links[z], path->root[i][k], v) : perdoz_2(info, info->rooms[path->root[i][k]]->links[z], path->root[i][k], v);
//				}
//				z++;
//			}
////			info->time[path->root[i][k]]->links[w] = v;
//			v++;
//			k++;
//		}
//		i++;
//	}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//	init_start(info, path);
//	fill_rest(info);
//}



//void delite(t_info *info, t_path *path)
//{
//	int i;
//	int k;
//	int w;
//	int v;
//	int z;
//
//	w = 0;
//	i = 0;
//	info->count_time = 0;
//	while (w < path->count_root)
//	{
//		info->count_time += path->len_root[w];
//		w++;
//	}
//	info->count_time -= (w * 2);
//
//
//
//	info->count_time += info->count_room;
//	info->time = (t_room **)malloc(sizeof(t_room *) * info->count_time);
//	w = 0;
//	v = 0;
//	while (v < info->count_room)
//	{
//		info->time[v] = NULL;
//		v++;
//	}
////	printf("count->time[v] = %p\n", info->time[v - 1]);
//
////						int d;
//
//	while (i < path->count_root)
//	{
//
//
//		k = 1;
//		while (k < path->len_root[i] - 1)
//		{
//			//I think it need do later
//			info->time[v] = (t_room *)malloc(sizeof(t_room));
//			info->time[v]->index = v;
//			info->time[v]->links_len = 1;
//			info->time[v]->links = (int *)malloc(sizeof(int));
//			info->time[v]->links[0] = path->root[i][k - 1];
//			info->time[v]->rebuild = -1;
//			info->time[v]->true_index = path->root[i][k];
//
//
//
//
//
//
//
//
//
//
//			info->time[path->root[i][k]] = (t_room *)malloc(sizeof(t_room));
//			info->time[path->root[i][k]]->index = path->root[i][k];
//			info->time[path->root[i][k]]->links_len = info->rooms[path->root[i][k]]->links_len - 1;
//			info->time[path->root[i][k]]->links = (int *)malloc(sizeof(int) * info->time[path->root[i][k]]->links_len);
//			info->time[path->root[i][k]]->rebuild = 10;
////			printf("index = %d | count->time[v] = %d\n", info->time[path->root[i][k]]->index, info->time[v]->links[0]);
//
//			z = 0;
//			w = 0;
//			while (z < info->rooms[path->root[i][k]]->links_len)
//			{
//				if (info->rooms[path->root[i][k]]->links[z] != path->root[i][k - 1] && info->rooms[path->root[i][k]]->links[z] != path->root[i][k + 1])
//				{
////					d = 0;
////					while (d < info->rooms[info->rooms[path->root[i][k]]->links[z]]->links_len)
////					{
////						printf("index = %d | link = %d\n", info->rooms[path->root[i][k]]->links[z], info->rooms[info->rooms[path->root[i][k]]->links[z]]->links[d]);
////						d++;
////					}
//
//
//
//
//
//
//
//
//					info->time[path->root[i][k]]->links[w++] = info->rooms[path->root[i][k]]->links[z];
//					!info->time[info->rooms[path->root[i][k]]->links[z]] ? perdoz(info, info->rooms[path->root[i][k]]->links[z], path->root[i][k], v) : perdoz_2(info, info->rooms[path->root[i][k]]->links[z], path->root[i][k], v);
//
//
////					d = 0;
////					while (d < info->time[info->rooms[path->root[i][k]]->links[z]]->links_len)
////					{
////						printf("time : index = %d | link = %d\n", info->time[info->rooms[path->root[i][k]]->links[z]]->index, info->time[info->rooms[path->root[i][k]]->links[z]]->links[d]);
////						d++;
////					}
////					printf("PAUSE\n");
//
//
//
//
//
//
//
//
//				}
//				z++;
//			}
//			info->time[path->root[i][k]]->links[w] = v;
//
////			d = 0;
////			while (d < info->time[path->root[i][k]]->links_len)
////			{
////				printf("time : index = %d | link = %d\n", info->time[path->root[i][k]]->index, info->time[path->root[i][k]]->links[d]);
////				d++;
////			}
////			printf("PAUSE\n");
//
//
//			v++;
//			k++;
//		}
//		i++;
//	}
//	info->time[info->start] = (t_room *)malloc(sizeof(t_room));
//	info->time[info->start]->index = info->start;
//	info->time[info->start]->links_len = info->rooms[info->start]->links_len - path->count_root;
//	info->time[info->start]->links = (int *)malloc(sizeof(int) * info->time[info->start]->links_len);
//	info->time[info->start]->rebuild = 1;
//
//	w = 0;
//	z = 0;
//	while (z < info->rooms[info->start]->links_len)
//	{
//		if (check_start_time(info->rooms[info->start]->links[z], path))
//			info->time[info->start]->links[w++] = info->rooms[info->start]->links[z];
//		z++;
//	}
//	fill_rest(info);
//
//
//}







void clean_del(t_info *info)
{
	int i;
	int w;

	w = 0;
	i = 0;
	while (i < info->count_time)
	{
		if (info->time[i]->rebuild == 0)
		{
		}
		else if (info->time[i]->rebuild == 1)
		{
			free(info->time[i]->links);
			free(info->time[i]);
		}
		else if (info->time[i]->rebuild == -1)
		{
			free(info->time[i]->links);
			free(info->time[i]);
		}
		else if (info->time[i]->rebuild == 10)
		{
			free(info->time[i]->links);
			free(info->time[i]);
		}
		i++;
	}
	free(info->time);
}





//int next_number(t_path *path, int index)
//{
//	int i;
//	int k;
//
//	i = 0;
//	while (i < path->count_root)
//	{
//		k = 0;
//		while (k < path->len_root[i])
//		{
//			if (index == path->root[i][k])
//				return (path->root[i][k - 1]);
//			k++;
//		}
//		i++;
//	}
//	return (0);
//}


//int check_denied(t_info *info, int index)
//{
//	int i;
//
//	i = 0;
//	while (i < info->count_den_link)
//	{
//		if (info->denied_link_start[i] == index)
//			return (0);
//		i++;
//	}
//	return (1);
//
//
//
//
//}



void free_pathes(t_info *info, t_path **path, int count)
{
	int i;
	int k;

	i = 0;
	while (i < count)
	{
		if (path[i] != info->marshroot)
		{
			k = 0;
			while (k < path[i]->count_root)
			{
				free(path[i]->root[k]);
				k++;
			}
			free(path[i]->len_root);
			free(path[i]->root);
			free(path[i]->count_ant);
			free(path[i]);
		}
		i++;
	}
	free(path);
}
















