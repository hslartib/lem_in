/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_init_checkorder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:52:25 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/11 18:52:26 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

int		info_islink(char *line, t_valid *v, int *find)
{
	char	**tmp;
	int		i;
	int 	ret;

	i = 0;
	tmp = ft_strsplit(line, '-');
	while (tmp[i])
		i++;
	if (i != 2)
		ret = 0;
	else if (i > 3 || !v->ant || !v->room || ft_strstr(tmp[0], " ") || ft_strstr(tmp[1], " "))
		ret = -1;
	else
	{
		ret = 1;
		*find = ret;
		v->link += ret;
	}
	ft_strdel_2d(&tmp);
//	printf("link-ret: %d\n", ret);
	return (ret);
}

int		info_isroom(char *line, t_valid *v, int *find)
{
	char	**tmp;
	int		i;
	int 	ret;

	i = 0;
	tmp = ft_strsplit(line, ' ');
	while (tmp[i])
		i++;
	if (i != 3)
		ret = 0;
	else if (i > 3 || !v->ant || v->link || !check_print(line) ||
			 !check_number(tmp[1]) || !check_number(tmp[2]))
		ret = -1;
	else
	{
		ret = 1;
		*find = ret;
		v->room += ret;
	}
	ft_strdel_2d(&tmp);
//	printf("room-ret: %d\n", ret);
	return (ret);
}

int		info_isant(char *line, t_valid *v, int *find)
{
	int 	ret;

	if (!check_number(line) || ft_strstr(line, "-"))
		ret = 0;
	else if (v->ant || v->link || v->room) {
		printf("ant -> line: %s | ant: %d | link: %d | room: %d\n", line, v->ant, v->link, v->room);
		ret = -1;
	}
	else
	{
		ret = 1;
		*find = ret;
		v->ant += ret;
	}
//	printf("ant-ret: %d\n", ret);
	return (ret);
}

int 		info_checkspecial(char *line, char *nextline, t_valid *v, int *find)
{
	if (!ft_strcmp(line, "##start"))
	{
		if (!v->ant || v->link || v->start || !nextline || ft_strstr(nextline, "-")) {
//			printf("special -> fuck you\n");
			return (-1);
		}
		v->start = 1;
		*find = 1;
	}
	else if (!ft_strcmp(line, "##end"))
	{
		if (!v->ant || v->link || v->end || !nextline || ft_strstr(nextline, "-")) {
//			printf("special -> fuck you\n");
			return (-1);
		}
		v->end = 1;
		*find = 1;
	}
//	printf("special -> sorry for what?\n");
	return (1);
}

int 		info_checkorder(t_info *info)
{
	t_valid v;
	int 	find;

	ft_bzero(&v, sizeof(t_valid));
	while (info->input[v.runner])
	{
		find = 0;
//		printf("main -> line: %s | ant: %d | room: %d | link: %d\n",info->input[v.runner], v.ant, v.room, v.link);
		if (info->input[v.runner][0] == '#' && info->input[v.runner][1] != '#')
			;
		else if (info_checkspecial(info->input[v.runner], info->input[v.runner + 1], &v, &find) < 0 && !find)
		{
			printf("special\n");
			return (lem_errmsg(info, MAP_WRONG_ORDER));
		}
		else if (info_isant(info->input[v.runner], &v, &find) < 0 && !find) {
			printf("ant\n");
			return (lem_errmsg(info, MAP_WRONG_ORDER));
		}
		else if (info_isroom(info->input[v.runner], &v, &find) < 0 && !find) {
			printf("room\n");
			return (lem_errmsg(info, MAP_WRONG_ORDER));
		}
		else if (info_islink(info->input[v.runner], &v, &find) < 0 && !find) {
			printf("link\n");
			return (lem_errmsg(info, MAP_WRONG_ORDER));
		}
		else if (!find) {
			printf("nothing -> find: %d\n", find);
			return (lem_errmsg(info, MAP_WRONG_ORDER));
		}
//		printf("find: %d\n\n", find);
		v.runner += 1;
	}
	return (ALLRIGHT);
}