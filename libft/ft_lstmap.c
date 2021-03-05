/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 11:39:35 by lstepany          #+#    #+#             */
/*   Updated: 2020/07/07 09:56:02 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *map;
	t_list *temp;

	if (lst == NULL)
		return (NULL);
	map = NULL;
	map = f(ft_lstnew(lst->content, lst->content_size));
	if (map == NULL)
		return (NULL);
	temp = map;
	lst = lst->next;
	while (lst != NULL)
	{
		temp->next = f(ft_lstnew(lst->content, lst->content_size));
		temp = temp->next;
		if (temp == NULL)
			return (NULL);
		lst = lst->next;
	}
	return (map);
}
