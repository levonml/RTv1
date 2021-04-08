/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:16:38 by lstepany          #+#    #+#             */
/*   Updated: 2021/04/08 00:16:39 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	intersect_ray_plane(t_data *data, t_ray *ray, int current_plane, float *t)
{
	t_vector	plane;
	
	if ((!data->plane) || (data->plane_count - 1) < current_plane)
		return (0);
	plane = vector_sub(&data->plane[current_plane].pos, &ray->start);
	data->a = dot_product(&data->plane[current_plane].normal, &plane);
	data->b = dot_product(&data->plane[current_plane].normal, &ray->dir);
	if (data->b == 0)
		return (0);
	data->t1 = (data->a / data->b);
	if (data->t1 > 0 && data->t1 < *t)
	{
		*t = data->t1;
		return (1);
	}
	return (0);
}
