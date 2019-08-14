/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:56:59 by hslartib          #+#    #+#             */
/*   Updated: 2019/04/13 20:06:29 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;
	void	*data;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
	{
		return (NULL);
	}
	if (content == NULL)
	{
		list->content = NULL;
		list->content_size = 0;
		list->next = NULL;
		return (list);
	}
	if (!(data = malloc(sizeof(void) * content_size + 1)))
		return (NULL);
	ft_memcpy(data, content, content_size);
	list->next = NULL;
	list->content_size = content_size;
	list->content = data;
	return (list);
}
