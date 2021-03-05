/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 09:23:07 by lstepany          #+#    #+#             */
/*   Updated: 2020/08/06 14:20:13 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include <stdlib.h>

int		ft_newline(char *str)
{
	int				j;

	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] == '\n')
			return (j);
		j++;
	}
	return (-1);
}

int		read_all(const int fd, char **store)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char			*temp;

	if (!(*store))
		*store = ft_strnew(0);
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		temp = ft_strjoin(*store, buf);
		free(*store);
		*store = temp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static	char	*store[MAX_FD];
	char			*temp;
	int				ret;
	int				t;

	if ((fd < 0) || (fd > 4096) || (ret = read_all(fd, &store[fd])) < 0)
		return (-1);
	if (ret == 0 && *store[fd] == '\0')
		return (0);
	if ((store[fd]) && (t = ft_newline(store[fd])) != -1)
	{
		*line = ft_strsub(store[fd], 0, t);
		temp = ft_strdup(ft_strchr(store[fd], '\n') + 1);
		free(store[fd]);
		store[fd] = temp;
		return (1);
	}
	if (ft_newline(store[fd]) == -1)
	{
		*line = ft_strdup(store[fd]);
		free(store[fd]);
		store[fd] = NULL;
		return (1);
	}
	return (-1);
}
