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

void				set_flags(t_info *info, int argc, char **argv)
{
	int i;

	i = 0;
	while (++i < argc)
		if (!ft_strcmp("-v", argv[i]))
			info->visual = 1;
}

int					main(int argc, char **argv)
{
	t_info			*info;
	int				i;

	if (!(info = (t_info *)malloc(sizeof(t_info))))
		return (0);
	info_init(info);
	set_flags(info, argc, argv);
	i = 0;
	while (i < info->count_room)
	{
		info->rooms[i]->index = i;
		i++;
	}
	if (check_end_start_link(info))
		output_start_end(info);
	else if (do_path(info) == -1)
		return (lem_errmsg(info, NO_SOLUTION));
	else
		output(info, info->marshroot);
	cleanup_info(info);
	return (0);
}
