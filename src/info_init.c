/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:01:33 by dbrady            #+#    #+#             */
/*   Updated: 2019/08/14 16:01:34 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/lem_strt.h"

char	*append(char *t, char c)
{
	char	*tmp;
	int		i;

	i = 0;
	if (t)
	{
		tmp = ft_strnew(ft_strlen(t + 1));
		ft_memcpy(tmp, t, ft_strlen(t));
		tmp[ft_strlen(t)] = '\0';
	}
	else
		tmp = ft_strnew(1);
	while (tmp[i])
		i += 1;
	tmp[i] = c;
	free(t);
	return (tmp);
}

char	**read_split(t_info *info)
{
	char	**tmp;
	int		t;
	char	buff[1024];

	t = -1;
	*tmp = (char **)malloc(sizeof(char *) * 24000);
	while (++t < 12000)
		*tmp[t] = NULL;
	t = 0;
	while (read(0, buff, 1))
	{
		if (buff[0] == '\n')
		{
			tmp[t] = append(tmp[t], '\n');
			t++;
		}
		else
			tmp[t] = append(tmp[t], buff[0]);
	}
	return (tmp);
}

void	info_init(t_info *info)
{
	t_room	**tmp;
	char 	**text;
	int 	i;

	i = -1;
	text = read_split(info);
	while (text[++i])
		printf("%s", text[i]);
}