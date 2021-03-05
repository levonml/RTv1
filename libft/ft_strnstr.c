/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 12:38:08 by lstepany          #+#    #+#             */
/*   Updated: 2020/06/29 01:22:05 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	k;
	int		j;

	if ((char*)little == NULL)
		return ((char*)big);
	else if (big[0] == '\0' && little[0] == '\0')
		return ("");
	k = 0;
	while (big[k] && (k < len))
	{
		j = 0;
		i = k;
		while ((little[j]) && (big[i] == little[j]) && (i < len))
		{
			j++;
			i++;
		}
		if (little[j] == '\0')
			return ((char*)(big + k));
		else
			k++;
	}
	return (NULL);
}
