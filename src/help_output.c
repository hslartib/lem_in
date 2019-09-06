/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:55:33 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/06 19:55:39 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

int					opredel_end(t_path *path, int *puti, int *z, int k)
{
	int			d;
	int			end;

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

void				vivod(t_path *path, int *puti, int *komnat, int i)
{
	komnat[i]++;
	printf("L%d-%d", i + 1, path->root[puti[i]][komnat[i]]);
	komnat[i] == path->len_root[puti[i]] - 1 ? komnat[i] = -1 : 0;
}

void				null_n(int *i1, int *i2, int *i3, int *i4)
{
	*i1 = 0;
	*i2 = 0;
	*i3 = 0;
	*i4 = 0;
}

void				opredel_path(t_info *info, t_path *path, int *puti, int *komnat)
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

void				finish_algo(t_info *info, t_path *path, int *puti, int *komnat)
{
	int i;

	i = 0;
	if (info->visual)
	{
		info->sdl_path = path;
		lem_sdl_control(info);
	}
	while (i < path->count_root)
		free(path->root[i++]);
	free(puti);
	free(komnat);
	free(path->count_ant);
	free(path->len_root);
	free(path->root);
	free(path);
}