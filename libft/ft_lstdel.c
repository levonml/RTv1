/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 08:12:14 by lstepany          #+#    #+#             */
/*   Updated: 2020/07/07 11:08:41 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *current;
	t_list *next_node;

	current = *alst;
	while (current != NULL)
	{
		next_node = current->next;
		del(current->content, current->content_size);
		free(current);
		current = next_node;
	}
	*alst = NULL;
}
