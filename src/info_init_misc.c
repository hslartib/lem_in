/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_init_misc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 02:06:52 by dbrady            #+#    #+#             */
/*   Updated: 2019/08/15 02:06:53 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/lem_strt.h"

int		rooms_find_name(t_room **rooms, char *name)
{
    int r;

    r = 0;
    while (rooms[r] && ft_strcmp(rooms[r]->name, name))
        r++;
    return (rooms[r] ? r : -1);
}

int		init_rooms(t_info *info, char **text)
{
	int		runner;
	int 	len;

	runner = next_value(info, text, 0) + 1;
	len = 0;
	while (!ft_strstr(text[runner], "-"))
	{
		if (text[runner][0] != '#')
			len += 1;
		runner += 1;
	}
	info->rooms = (t_room **)malloc(sizeof(t_room *) * (len + 1));
	ft_bzero(info->rooms, sizeof(t_room *) * (len + 1));
	return (len);
}