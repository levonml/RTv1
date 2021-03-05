/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 11:46:09 by lstepany          #+#    #+#             */
/*   Updated: 2020/06/19 15:22:31 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	h;

	j = 0;
	while (dest[j])
		j++;
	h = ft_strlen(src);
	if (size <= j)
		return (size + h);
	else
	{
		i = 0;
		while ((src[i]) && (i < (size - j - 1)))
		{
			dest[j + i] = src[i];
			i++;
		}
		dest[j + i] = '\0';
		return (h + j);
	}
	return (0);
}
