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

#include "./inc/lem_strt.h"

//int 	info_valid_text(t_info *info)
//{
//	int		i;
//
//	i = 0;
//	while (info->input[i])
//}

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
	if(info->start < 0 || info->end < 0)
	{
		lem_errmsg(info, NO_STARTEND);
		error = 1;
	}
	return (error ? ERROR : ALLRIGHT);
}