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

int 	check_number(char *line)
{
	char *buff;

	buff = line;
	while (*line)
	{
		if (!ft_isdigit(*line) && *line != '-' && *line != '+')
			return (0);
		line += 1;
	}
	return (buff == line ? 0 : 1);
}

int 	check_print(char *line)
{
	char *buff;

	buff = line;
	while (*line)
	{
		if (*line < 32)
			return (0);
		line += 1;
	}
	return (buff == line ? 0 : 1);
}

int		info_valid(t_info *info)
{
	int error;

	error = 0;
	if (!info->count_room && ++error)
		lem_errmsg(info, NO_ROOMS);
	if ((info->count_ants <= 0 || info->count_ants > INT_MAX) && ++error)
		lem_errmsg(info, WRONG_ANTS);
	if ((info->start < 0 || info->end < 0) && ++error)
		lem_errmsg(info, NO_STARTEND);
	if (info->start == info->end && ++error)
		lem_errmsg(info, START_IS_END);
	return (error ? ERROR : ALLRIGHT);
}
