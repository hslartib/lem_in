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

#include <sandbox.h>
#include "../inc/lem_strt.h"

int help_build(t_path *path, t_info *info, char **mas)
{
	int i;
	int len;

	len = 0;
	while (mas[len])
		len++;
	path->len_root[path->count_root - 1] = len;
	path->root[path->count_root - 1] = (int *)malloc(sizeof(int) * len);
	i = 0;
	len = 0;
	while (mas[i])
	{
		path->root[path->count_root - 1][i] = ft_atoi(mas[i]);
		free(mas[i]);
		if (path->root[path->count_root - 1][i] >= info->count_room)
			path->root[path->count_root - 1][i] = info->time[path->root[path->count_root - 1][i]]->true_index;
		if (i > 0 && path->root[path->count_root - 1][i] == path->root[path->count_root - 1][i - 1])
			len++;
		i++;
	}
	return (len);
}

void build_path_den(char *str, t_path *path, t_info *info)
{
	int i;
	int len;
	int z;
	int *op;
	char **mas;

	mas = ft_strsplit(str, '-');
	len = help_build(path, info, mas);
	free(str);
	op = path->root[path->count_root - 1];
	path->len_root[path->count_root - 1] -= len;
	path->root[path->count_root - 1] = (int *)malloc(sizeof(int) * path->len_root[path->count_root - 1]);
	i = 0;
	z = 0;
	while (i < path->len_root[path->count_root - 1] + len)
	{
		if (i == 0)
			path->root[path->count_root - 1][z++] = op[i];
		else if (i > 0 && op[i] != op[i - 1])
			path->root[path->count_root - 1][z++] = op[i];
		i++;
	}
	free(mas);
	free(op);
}

void		rebuild_path(t_path **path, int index)
{
	int k;
	int z;

	z = path[index]->count_root - 1;
	while (z >= 0)
	{
		k = z - 1;
		while (k >= 0)
		{
			double_path(path[index], z, k);
			k--;
		}
		z--;
	}
}

void		build_path(t_info *info, t_path *path, int index, int lamp)
{
    int		k;
    int		l;

    k = 0;
    path->root[path->count_root - 1][path->score--] = index;
    while (k < info->rooms[index]->links_len && index != info->start)
    {
        if (info->len_path[index] - 1 == info->len_path[info->rooms[index]->links[k]] && lamp && !path->check)
        {
            l = path->score;
            build_path(info, path, info->rooms[index]->links[k], 1);
            !path->check ? path->score = l : 0;
        }
        k++;
    }
    index == info->end ? free(info->len_path) : 0;
}

void		vrtc_den_1(t_info *info, int index, char *str, int k)
{
	info->len_path[info->time[index]->links[k]] = info->len_path[index] - 1;
	len_vrtc_den(info, info->time[index]->links[k], str);
}

void		vrtc_den_2(t_info *info, int index, char *str, int k)
{
	info->len_path[info->time[index]->links[k]] = info->len_path[index] + 1;
	len_vrtc_den(info, info->time[index]->links[k], str);
}

void		vrtc_den_3(t_info *info, int index, char *str, int k)
{
	info->len_path[info->time[index]->links[k]] = info->len_path[index];
	len_vrtc_den(info, info->time[index]->links[k], str);
}

void		vrtc_den_4(t_info *info, int index, char *str, int k)
{
	info->len_path[info->time[index]->links[k]] = info->len_path[index] + 1;
	len_vrtc_den(info, info->time[index]->links[k], str);
}

char		*help_str_vrtc(char *str, int index, t_info *info)
{
	char	*lari;
	char	*dodo;
	char	*namnam;

	lari = ft_strjoin(str, "-");
	namnam = ft_itoa(index);
	dodo = ft_strjoin(lari, namnam);
	free(lari);
	free(namnam);
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

void		len_vrtc_den(t_info *info, int index, char *str)
{
    int k;

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

void		weight_den(t_info *info)
{
	int		i;
	char	*str;

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

int			find_max(t_path *path)
{
	int		i;
	int		max;

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

int			find_len(t_path *path, t_info *info, int max)
{
	int i;
	int len;

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

int			find_mod(t_path *path, t_info *info, int max, int len)
{
	int mod;
	int i;

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

void		bit(t_path *path, int mod)
{
	int i;

	i = 0;
	while (i < mod)
	{
		path->count_ant[i]++;
		i++;
	}
}

void		do_count(t_info *info, t_path *path)
{
	int		i;
	int		max;
	int		len;
	int		mod;

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

void		init_path0(t_path **path)
{
	path[0] = (t_path *)malloc(sizeof(t_path));
	path[0]->root = (int **)malloc(sizeof(int *));
	path[0]->len_root = (int *)malloc(sizeof(int));
	path[0]->count_root = 1;
	path[0]->check = 0;
}

void		init_path0_continue(t_info *info, t_path **path)
{
	path[0]->len_root[0] = info->len_path[info->end] + 1;
	path[0]->root[0] = (int *)malloc(sizeof(int) * path[0]->len_root[0]);
	path[0]->score = path[0]->len_root[0] - 1;
}

void		vibor_krotchaishego(t_info *info, t_path *path)
{
	info->marshroot = path;
	info->count_string = path->itog;
}

void		init_path_i(t_path **path, int i)
{
	path[i] = (t_path *)malloc(sizeof(t_path));
	path[i]->root = (int **)malloc(sizeof(int *) * (i + 1));
	path[i]->len_root = (int *)malloc(sizeof(int) * (i + 1));
	path[i]->count_root = i + 1;
}

int			do_path_part_1(t_info *info, t_path **path)
{
	init_path0(path);
	weight(info);
	if (info->len_path[info->end] == 1000000)
		return (-1);
	init_path0_continue(info, path);
	build_path(info, path[0], info->end, 1);
	do_count(info, path[0]);
	vibor_krotchaishego(info, path[0]);
	return (1);
}

void		do_path_part_2(t_info *info, t_path **path, int i)
{
	delite(info, path[i - 1]);
	init_path_i(path, i);
	weight_den(info);
}

void		do_path_part_3(t_info *info, t_path **path, int i)
{
	build_path_den(info->path, path[i], info);
	copy_prepath(path, i);
	rebuild_path(path, i);
	do_count(info, path[i]);
}

void		free_path0(t_path **path, t_info *info)
{
	free(path[0]);
	free(path[0]->root);
	free(path[0]->len_root);
	free(path);
	free(info->len_path);
}

int			do_path(t_info *info)
{
	t_path	**path;
	int		i;
	int		rex;

	rex = 1;
	path = (t_path **)malloc(sizeof(t_path *) *
		info->rooms[info->start]->links_len);
	if (do_path_part_1(info, path) == -1)
	{
		free_path0(path, info);
		return (-1);
	}
	i = 1;
	while (i < info->rooms[info->start]->links_len && rex)
	{
		do_path_part_2(info, path, i);
		if (info->len_path[info->end] == 1000000)
			rex = 0;
		else
		{
			do_path_part_3(info, path, i);
			if (path[i]->itog <= info->count_string && path[i]->check)
				vibor_krotchaishego(info, path[i]);
			else
				rex = 0;
		}
		clean_del(info);
		i++;
	}
	free_pathes(info, path, i);
	return (1);
}

void		len_vrtc(t_info *info, int nbr)
{
	int		k;
	int		i;

	i = 0;
	while (i < info->count_room)
	{
		if (info->len_path[i] == nbr)
		{
			k = 0;
			while (k < info->rooms[i]->links_len)
			{
				if (info->len_path[info->rooms[i]->links[k]]
				> info->len_path[i] + 1)
					info->len_path[info->rooms[i]->links[k]] =
						info->len_path[i] + 1;
				k++;
			}
		}
		i++;
	}
	if (!check_len(info, nbr + 1))
		len_vrtc(info, nbr + 1);
}

void		weight(t_info *info)
{
	int		i;

	info->len_path = (int *)malloc(sizeof(int) * info->count_room);
	i = 0;
	while (i < info->count_room)
		info->len_path[i++] = 1000000;
	info->len_path[info->start] = 0;
	i = 0;
	while (i < info->rooms[info->start]->links_len)
	{
		info->len_path[info->rooms[info->start]->links[i]] = 1;
		i++;
	}
	if (!check_len(info, 1))
		len_vrtc(info, 1);
}

int			opredel_end(t_path *path, int *puti, int *z, int k)
{
	int		d;
	int		end;

	end = 0;
	d = 0;
	while (d < path->count_root)
	{
		if (path->count_ant[d] >= k)
		{
			puti[*z] = d;
			*z += 1;
			end++;
		}
		d++;
	}
	return (end);
}

void			vivod(t_path *path, int *puti, int *komnat, int i)
{
	komnat[i]++;
	printf("L%d-%d", i + 1, path->root[puti[i]][komnat[i]]);
	komnat[i] == path->len_root[puti[i]] - 1 ? komnat[i] = -1 : 0;
}

void			null_n(int *i1, int *i2, int *i3, int *i4)
{
	*i1 = 0;
	*i2 = 0;
	*i3 = 0;
	*i4 = 0;
}

void			opredel_path(t_info *info, t_path *path, int *puti, int *komnat)
{
	t_opredel	n;

	null_n(&n.last, &n.end, &n.k, &n.z);
	while (1)
	{
		n.k++;
		while (komnat[n.last] == -1)
			n.last++;
		n.end += opredel_end(path, puti, &n.z, n.k);
		n.i = n.last;
		while (n.i < n.end)
		{
			if (komnat[n.i] != -1)
			{
				n.i != n.last ? printf(" ") : 0;
				vivod(path, puti, komnat, n.i);
			}
			n.i++;
		}
		if (n.last == info->count_ants)
			break ;
		else
			printf("\n");
	}
}

void			output(t_info *info, t_path *path)
{
	int			i;
	int			*puti;
	int			*komnat;

	i = 0;
	puti = (int *)malloc(sizeof(int) * info->count_ants);
	komnat = (int *)malloc(sizeof(int) * info->count_ants);
	while (i < info->count_ants)
		komnat[i++] = 0;
	opredel_path(info, path, puti, komnat);
	i = 0;
	while (i < path->count_root)
		free(path->root[i++]);
	free(puti);
	free(komnat);
	free(path->count_ant);
	free(path->len_root);
	free(path->root);
	free(path);
}

int				check_end_start_link(t_info *info)
{
	int			i;

	i = 0;
	while (i < info->rooms[info->start]->links_len)
	{
		if (info->rooms[info->start]->links[i] == info->end)
			return (1);
		i++;
	}
	return (0);
}

void			output_start_end(t_info *info)
{
	int i;

	i = 0;
	while (i < info->count_ants)
	{
		printf("L%d-%d ", i + 1, info->end);
		i++;
	}
	printf("\n");
}

int					main(void)
{
	t_info			*info;
	int				i;

	if (!(info = (t_info *)malloc(sizeof(t_info))))
		return (0);
	info_init(info);
	i = 0;
	while (i < info->count_room)
	{
		info->rooms[i]->index = i;
		i++;
	}
	if (check_end_start_link(info))
		output_start_end(info);
	else if (do_path(info) == -1)
	{
		printf("hana");
	}
	else
		output(info, info->marshroot);
	cleanup_info(info);
	return (0);
}
