/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 15:01:35 by dbrady            #+#    #+#             */
/*   Updated: 2019/08/16 15:01:36 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

int 	info_islink(char *line)
{
	char	**tmp;
	int 	i;

	i = 0;
	tmp = ft_strsplit(line, '-');
	while (tmp[i])
		i++;
	if (i != 2)
	{
		ft_strdel_2d(&tmp);
		return (0);
	}
	ft_strdel_2d(&tmp);
	return (1);
}

int 	info_isroom(char *line)
{
	char	**tmp;
	int 	i;

	i = 0;
	tmp = ft_strsplit(line, ' ');
	while (tmp[i])
		i++;
	if (i != 3 || !ft_isdigit(tmp[1][0]) || !ft_isdigit(tmp[2][0]))
	{
		ft_strdel_2d(&tmp);
		return (0);
	}
	ft_strdel_2d(&tmp);
	return (1);
}

int		info_isant(char *line)
{
	char	**tmp;
	int 	i;

	i = 0;
	if (info_islink(line) || info_islink(line))
		return (0);
	tmp = ft_strsplit(line, ' ');
	while (tmp[i])
		i++;
	if (i > 1 || !ft_isdigit(tmp[0][0]))
	{
		ft_strdel_2d(&tmp);
		return (0);
	}
	ft_strdel_2d(&tmp);
	return (1);
}

int 	info_checkorder(t_info *info)
{
	int jarl[5];

	ft_bzero(jarl, sizeof(int) * 5);
//	printf("start: jcount0->%d | ja1->%d | jt2->%d | jl3->%d | jret4->%d\n", jarl[0], jarl[1], jarl[2], jarl[3], jarl[4]);
	while (info->input[jarl[0]])
	{
		if (info->input[jarl[0]][0] == '#')
			jarl[0] += 1;
		else if (info_isant(info->input[jarl[0]]) && (jarl[0] += 1))
			(jarl[1] || jarl[2] || jarl[3]) ? (jarl[4] = -1) : (jarl[1] += 1);
		else if (info_isroom(info->input[jarl[0]]) && (jarl[0] += 1))
			(jarl[3] || !jarl[1]) ? (jarl[4] = -1) : (jarl[2] += 1);
		else if (info_islink(info->input[jarl[0]]) && (jarl[0] += 1))
			(!jarl[1] || !jarl[2]) ? (jarl[4] = -1) : (jarl[3] += 1);
	}
	return (!jarl[4] ? 1 : 0);
}

int 	info_valid(t_info *info)
{
	int error;

	error = 0;
	if (!info->count_room)
	{
		lem_errmsg(info, NO_ROOMS);
		error = 1;
	}
	if (!info->count_ants)
	{
		lem_errmsg(info, NO_ANTS);
		error = 1;
	}
	if (info->start < 0 || info->end < 0)
	{
		lem_errmsg(info, NO_STARTEND);
		error = 1;
	}
	if (info->count_ants < 0 )
	{
		lem_errmsg(info, NEGATIVE_ANTS);
		error = 1;
	}
	return (error ? ERROR : ALLRIGHT);
}