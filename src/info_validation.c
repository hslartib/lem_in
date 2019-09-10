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

int		info_islink(char *line)
{
	char	**tmp;
	int		i;

	i = 0;
//	printf("islink~\n");
	tmp = ft_strsplit(line, '-');
//	printf("islink -> post-split~\n");
	while (tmp[i])
		i++;
//	printf("islink -> post-while~\n");
	if (i != 2)
	{
		ft_strdel_2d(&tmp);
//		printf("iflink\n");
		return (0);
	}
//	printf("islink -> post-2d~\n");
	ft_strdel_2d(&tmp);
	return (1);
}

int		info_isroom(char *line)
{
	char	**tmp;
	int		i;

	i = 0;
//	printf("isroom~\n");
	tmp = ft_strsplit(line, ' ');
//	printf("isroom -> post-split~\n");
	while (tmp[i])
		i++;
//	printf("islink -> post-room~\n");
	if (i != 3 || !ft_isdigit(tmp[1][0]) || !ft_isdigit(tmp[2][0]))
	{
//		printf("ifroom\n");
		ft_strdel_2d(&tmp);
		return (0);
	}
//	printf("isroom -> post-2d~\n");
	ft_strdel_2d(&tmp);
	return (1);
}

int		info_isant(char *line)
{
	char	**tmp;
	int		i;

	i = 0;
//	printf("isant~\n");
	if (info_islink(line))
		return (0);
	tmp = ft_strsplit(line, ' ');
//	printf("isant -> post-split~\n");
	while (tmp[i])
		i++;
//	printf("isant -> post-while~\n");
	if (i > 1 || !tmp[0] || !ft_isdigit(tmp[0][0]))
	{
//		printf("ifant\n");
		ft_strdel_2d(&tmp);
		return (0);
	}
//	printf("isant -> post-2d~\n");
	ft_strdel_2d(&tmp);
	return (1);
}

int		info_checkorder(t_info *info)
{
	int jarl[5];

	ft_bzero(jarl, sizeof(int) * 5);
	while (info->input[jarl[0]])
	{
		if (info->input[jarl[0]][0] == '#')
			jarl[0] += 1;
		else if (ft_strstr(info->input[jarl[0]], " ")
			&& (strstr(info->input[jarl[0]], "-")
			|| strstr(info->input[jarl[0]], "L")))
			return (lem_errmsg(info, MAP_INVALID_NAME));
		else if (info_isant(info->input[jarl[0]]) && (jarl[0] += 1))
			(jarl[1] || jarl[2] || jarl[3]) ? (jarl[4] = -1) : (jarl[1] += 1);
		else if (info_isroom(info->input[jarl[0]]) && (jarl[0] += 1))
			(jarl[3] || !jarl[1]) ? (jarl[4] = -1) : (jarl[2] += 1);
		else if (info_islink(info->input[jarl[0]]) && (jarl[0] += 1))
			(!jarl[1] || !jarl[2]) ? (jarl[4] = -1) : (jarl[3] += 1);
		else
			jarl[0] += 1;
	}
	return (!jarl[4] ? ALLRIGHT : lem_errmsg(info, MAP_WRONG_ORDER));
}

int		info_valid(t_info *info)
{
	int error;

	error = 0;
	if (!info->count_room && ++error)
		lem_errmsg(info, NO_ROOMS);
	if ((info->count_ants <= 0 || info->count_ants > INT_MAX) && ++error)
		lem_errmsg(info, WRONG_ANTS);
	if ((info->start < 0 || info->end < 0) && ++error)
		lem_errmsg(info, NO_STARTEND);
	if (info->count_ants < 0 && ++error)
		lem_errmsg(info, NEGATIVE_ANTS);
	return (error ? ERROR : ALLRIGHT);
}
