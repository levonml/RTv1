/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helping_ft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:16:05 by lstepany          #+#    #+#             */
/*   Updated: 2021/04/08 00:16:06 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		max_num(int a, int b, int c, int d)
{
	if (a < b)
		a = b;
	if (a < c)
		a = c;
	if (a < d)
		a = d;
	return (a);
}

float	ft_abs(float t)
{
	if (t < 0)
		return (-t);
	return (t);
}

void	put_message(char *str)
{
	ft_putstr(str);
	exit(0);
}

t_shape	*allocate(t_shape *shape, int num)
{
	if (!(shape = (t_shape *)malloc(sizeof(t_shape) * num)))
		exit(0);
	return (shape);
}
int compere(t_ray r1, t_ray r2)
{
	if(r1.start.x == r2.start.x && r1.start.y == r2.start.y \
	&& r1.start.z == r2.start.z)
		return(1);
	return(0);
}
