/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:47:55 by hslartib          #+#    #+#             */
/*   Updated: 2019/04/17 20:38:59 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*norm;
	t_list	*lord;

	if (!lst || !f)
		return (NULL);
	if (!(lord = f(lst)))
		return (NULL);
	norm = lord;
	while (lst->next)
	{
		if (!(lord->next = f(lst->next)))
		{
			while (norm)
			{
				lord = norm->next;
				free(norm);
				norm = lord;
			}
			return (NULL);
		}
		lst = lst->next;
		lord = lord->next;
	}
	return (norm);
}
