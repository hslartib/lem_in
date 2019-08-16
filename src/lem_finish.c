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

#include "./inc/lem_strt.h"

int		lem_errmsg(t_info *info, int errcode)
{
	if (errcode == NO_ROOMS)
		write(1, "Error : No rooms\n", 17);
	else if (errcode == NO_ANTS)
		write(1, "Error : No ants\n", 9);
	else if (errcode == NO_STARTEND)
		write(1, "Error : No start and/or end rooms\n", 34);
	else if (errcode == MULTIPLE_STARTEND)
	{
		write(1, "Error : Multiple start and/or end rooms\n", 40);
		return (-1);
	}
	cleanup_info(info);
	return (errcode);
}