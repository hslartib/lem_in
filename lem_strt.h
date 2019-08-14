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

#include "get_next_line.h"
#include "./libft/libft.h"

typedef struct		a_ant
{
	int				strt_nd[2];
	char			**room;
	char			**link;
	int				number;
}					t_ant;

#endif
