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

#include "lem_strt.h"

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

char	**read_split()
{
	char	**tmp;
	int		t;

	t = -1;
	tmp = (char **)malloc(sizeof(char *) * 100000);
	while (++t < 100000)
		tmp[t] = NULL;
	t = 0;
	while (get_next_line(0, tmp + t) > 0)
		t++;
	free(tmp[t]);
	tmp[t] = NULL;
	return (tmp);
}