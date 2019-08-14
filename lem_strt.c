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

#include "lem_strt.h"

int check_room(char **mas)
{
	int i;

	i = 0;
	while (mas[i])
		i++;

//	printf("check = %d\n", i);

	return (i != 3 ? 0 : 1);
}

char **creatlink(nbr)
{
	char **mas;
	int i;

	i = 0;
	if (!(mas = (char **)malloc(sizeof(char *) * (nbr + 1))))
		return (NULL);
	while (i < nbr)
	{
		if (!(mas[i] = ft_strnew(nbr)))
		{
			i--;
			while (i >= 0)
				free(mas[i--]);
			free(mas);
			return (NULL);
		}
		ft_memset(mas[i], '0', nbr);
		i++;
	}
	mas[i] = NULL;
	return (mas);
}

int find_link(char **mas, char *str)
{
	int i;

	i = 0;
	while (mas[i])
	{
		if (!ft_strcmp(str, mas[i]))
			return (i);
		i++;
	}
	return (-1);
}

void validread(t_ant *ant, int fd)
{
	char *lamb;
	char *str;
	char **mas;
	int i;
	int index;

	index = 0;
	str = ft_strnew(0);
	fd = 0;
	i = -1;
//	get_next_line(fd, &lamb);
//	ant->number = ft_atoi(lamb);
//	free(lamb);

	while (get_next_line(fd, &lamb))
	{
		if (!ft_strcmp(lamb, "##start"))
			ant->strt_nd[0] = i + 1;
		else if (!ft_strcmp(lamb, "##end"))
			ant->strt_nd[1] = i + 1;
//		else if (lamb[0] == '#')
//			i = i;
		else if (!index)
		{
			mas = ft_strsplit(lamb, ' ');
			if (check_room(mas))
			{
				i++;
//				printf("%d\n", i);
				if (str[0] != '\0')
					str = ft_strjoin(str, "#");
				str = ft_strjoin(str, mas[0]);
			}
			else
			{
//				printf("%s\n", str);



				ant->link = creatlink(i + 1);
				ant->room = ft_strsplit(str, '#');
				index = 1;
				mas = ft_strsplit(lamb, '-');
				ant->link[find_link(ant->room, mas[0])][find_link(ant->room, mas[1])] = '1';
				ant->link[find_link(ant->room, mas[1])][find_link(ant->room, mas[0])] = '1';
			}
		}
		else
		{
			mas = ft_strsplit(lamb, '-');
//			printf("%d\n", i);
//			printf("%s\n", mas[0]);
//			printf("%s\n", mas[1]);
//			printf("f = %d\n", find_link(ant->room, mas[0]));
//			printf("f = %d\n", find_link(ant->room, mas[1]));
			ant->link[find_link(ant->room, mas[0])][find_link(ant->room, mas[1])] = '1';
			ant->link[find_link(ant->room, mas[1])][find_link(ant->room, mas[0])] = '1';
		}
		free(lamb);
	}


	i = 0;
	while (ant->room[i])
	{
		printf("%s\n", ant->room[i]);
		i++;
	}
	i = 0;
	while (ant->link[i])
	{
		printf("%s\n", ant->link[i]);
		i++;
	}
	printf("%d - %d\n", ant->strt_nd[0], ant->strt_nd[1]);
}

int main()
{
	t_ant *ant;

	if (!(t_ant *)malloc(sizeof(t_ant)))
		return (0);
	validread(ant, 0);
	
	return (0);
}
