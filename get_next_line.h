/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 17:39:36 by hslartib          #+#    #+#             */
/*   Updated: 2019/05/03 17:34:23 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE  21

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "./libft/libft.h"

typedef struct		s_jon
{
	int				svd;
	char			*mod;
	struct s_jon	*next;
}					t_jon;
int					get_next_line(const int fd, char **line);
#endif
