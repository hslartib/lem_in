/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:57:22 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/06 19:57:24 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_strt.h"

void				output(t_info *info, t_path *path)
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
	finish_algo(info, path, puti, komnat);
}

int					check_end_start_link(t_info *info)
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

void				output_start_end(t_info *info)
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
