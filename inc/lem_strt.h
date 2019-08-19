/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_strt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 12:58:29 by hslartib          #+#    #+#             */
/*   Updated: 2019/08/13 12:58:31 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "./libft/libft.h"

enum 				e_errcode
{
	ALLRIGHT,
	ERROR,
	NO_ROOMS,
	NO_ANTS,
	NO_STARTEND,
	MULTIPLE_STARTEND,
	NO_SOLUTION,
	LINK_TO_GHOST,
	NEGATIVE_ANTS,
	MAP_WRONG_ORDER
};

typedef struct		s_room
{
	char			*name;
	int				*links;
	int 			coord_x;
	int 			coord_y;
	int				links_len;
	char			*all_path;
}					t_room;

typedef struct		s_info
{
	int				count_ants;
	int				start;
	int				end;
	t_room			**rooms;
	int				count_room;
	int				*len_path;
	char			**input;
}					t_info;


/*
** info_init related functions
*/
int					info_init(t_info *info);
int					rooms_find_name(t_room **rooms, char *name);
int					next_value(t_info *info, char **text, int i);
int					init_rooms(t_info *info, char **text);
int					info_valid(t_info *info);
int					info_checkorder(t_info *info);

/*
** finish related functions
*/
void				cleanup_info(t_info *info);
int					lem_errmsg(t_info *info, int errcode);

#endif
