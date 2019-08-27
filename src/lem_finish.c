/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_finish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 15:34:25 by dbrady            #+#    #+#             */
/*   Updated: 2019/08/16 15:34:26 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

int 	lem_moreerrmsg(int errcode)
{
	int ret;

	ret = 0;
	if (errcode == NO_ROOMS && ++ret)
		write(1, "Error : No rooms\n", 17);
	else if (errcode == NO_ANTS && ++ret)
		write(1, "Error : No ants\n", 16);
	else if (errcode == NO_STARTEND && ++ret)
		write(1, "Error : No start and/or end rooms\n", 34);
	else if (errcode == MAP_WRONG_ORDER && ++ret)
		write(1, "Error : Map is not well formatted\n", 34);
	return (ret);
}

int		lem_errmsg(t_info *info, int errcode)
{
	static int cleanup = 0;

	if (!lem_moreerrmsg(errcode) && errcode == MULTIPLE_STARTEND)
	{
		write(1, "Error : Multiple start and/or end rooms\n", 40);
		cleanup_info(info);
		cleanup = 1;
		return (-3);
	}
	else if (errcode == LINK_TO_GHOST)
		write(1, "Error : linking to a ghost room\n", 32);
	else if (errcode == NEGATIVE_ANTS)
		write(1, "Error : negative number of ants\n", 32);
	if (!cleanup)
	{
		cleanup_info(info);
		cleanup = 1;
	}
	return (errcode);
}