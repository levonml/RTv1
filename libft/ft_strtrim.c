/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 22:54:36 by lstepany          #+#    #+#             */
/*   Updated: 2020/07/07 10:13:00 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		l;
	char	*trim;

	i = 0;
	while (s[i] == '\n' || s[i] == '\t' || s[i] == ' ')
		i++;
	l = ft_strlen(s) - 1;
	while (s[l] == '\n' || s[l] == '\t' || s[l] == ' ')
		l--;
	if (s[i] == '\0')
		return ("");
	trim = ft_strsub(s, i, l - i + 1);
	return (trim);
}
