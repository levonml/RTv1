/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 10:31:55 by lstepany          #+#    #+#             */
/*   Updated: 2020/06/28 00:23:00 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;
	int k;

	if (haystack[0] == '\0' && needle[0] == '\0')
		return ("");
	k = 0;
	while (haystack[k])
	{
		j = 0;
		i = k;
		while ((needle[j]) && (haystack[i] == needle[j]))
		{
			j++;
			i++;
		}
		if (needle[j] == '\0')
			return ((char*)(haystack + k));
		else
			k++;
	}
	return (NULL);
}
