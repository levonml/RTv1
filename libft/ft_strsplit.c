/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 09:39:42 by lstepany          #+#    #+#             */
/*   Updated: 2020/06/23 13:32:36 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	size_t	ft_len(char const *s1, char c, size_t i)
{
	size_t	temp;

	temp = i;
	while ((s1[i] != c) && (s1[i]))
		i++;
	i = i - temp;
	return (i);
}

static	size_t	ft_start(char const *s1, char c, size_t i)
{
	while (s1[i] == c)
		i++;
	return (i);
}

static	size_t	arr_num(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s[i] != c)
		j++;
	i++;
	while (s[i])
	{
		if ((s[i] != c) && (s[i - 1] == c))
			j++;
		i++;
	}
	return (j);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**split;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	start;

	j = arr_num(s, c);
	split = (char**)malloc(sizeof(char*) * (j + 1));
	if (split == NULL)
		return (NULL);
	i = 0;
	k = j;
	j = 0;
	while (i < k)
	{
		start = ft_start(s, c, j);
		split[i] = ft_strsub(s, start, ft_len(s, c, start));
		j = start + ft_len(s, c, start);
		i++;
	}
	split[i] = NULL;
	return (split);
}
