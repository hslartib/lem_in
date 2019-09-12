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

int		check_number(char *line)
{
	char	*buff;
	int		minus;
	int		plus;
	int		digit;

	buff = line;
	minus = 0;
	plus = 0;
	digit = 0;
	while (*line)
	{
		if ((*line == '+' && plus) || (*line == '-' && minus))
			return (0);
		else if ((*line == '+' || *line == '-') && digit)
			return (0);
		else if (*line == '+' || *line == '-')
			(*line == '+') ? (plus = 1) :
			(minus = 1);
		else if (!ft_isdigit(*line))
			return (0);
		else
			digit = 1;
		line += 1;
	}
	return (buff == line ? 0 : 1);
}

int		check_print(char *line)
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

int		check_duplicate(t_info *info)
{
	int			i;
	int			j;
	t_room		*buff;

	i = 0;
	j = 0;
	while (i < info->count_room)
	{
		buff = info->rooms[i];
		while (j < info->count_room)
		{
			if (i != j && (!ft_strcmp(buff->name, info->rooms[j]->name) ||
				(buff->coord_x == info->rooms[j]->coord_x &&
				buff->coord_y == info->rooms[j]->coord_y)))
				return (1);
			j += 1;
		}
		i += 1;
		j = 0;
	}
	return (0);
}

int		info_valid(t_info *info)
{
	int error;

	error = 0;
	if (!info->count_room && ++error)
		lem_errmsg(info, NO_ROOMS);
	else if ((info->count_ants <= 0 || info->count_ants > INT_MAX) && ++error)
		lem_errmsg(info, WRONG_ANTS);
	else if ((info->start < 0 || info->end < 0) && ++error)
		lem_errmsg(info, NO_STARTEND);
	else if (info->start == info->end && ++error)
		lem_errmsg(info, START_IS_END);
	else if (check_duplicate(info) && ++error)
		lem_errmsg(info, DUP_ROOMS);
	return (error ? ERROR : ALLRIGHT);
}
