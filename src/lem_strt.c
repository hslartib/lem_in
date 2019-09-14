/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_strt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 12:37:57 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/14 15:35:01 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sandbox.h>
#include "../inc/lem_strt.h"

void				umenshaem_do_path1(t_info *info, t_path ***path, int *rex,
	int *i)
{
	*i = 1;
	*rex = 1;
	*path = (t_path **)malloc(sizeof(t_path *) *
		info->rooms[info->start]->links_len);
}

void				umenshaem_do_path2(int *rex, int *i)
{
	*rex = 0;
	*i = *i - 1;
}

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
	if (info_init(info) != ALLRIGHT)
		return (0);
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
