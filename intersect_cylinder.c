/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:16:32 by lstepany          #+#    #+#             */
/*   Updated: 2021/04/08 00:16:33 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vector	rotate(t_data *data, int current)
{
	data->cylinder[current].axis = data->vertical;
	data->cylinder[current].axis = rot_x(data->cylinder[current].axis, \
	data->cylinder[current].cylinder_rot_x[current]);
	data->cylinder[current].axis = rot_y(data->cylinder[current].axis, \
	data->cylinder[current].cylinder_rot_y[current]);
	data->cylinder[current].axis = rot_z(data->cylinder[current].axis, \
	data->cylinder[current].cylinder_rot_z[current]);		
	return(data->cylinder[current].axis);
}
int		intersect_ray_cylinder(t_data *data, t_ray *ray, int current, float *t)
{
	if (!data->cylinder || (data->cylinder_count - 1) < current)
		return (0);
	data->cylinder[current].axis = rotate(data, current);
	data->temp2 = dot_product(&ray->dir, &data->cylinder[current].axis);
	data->a = pow(data->temp2, 2) - 1;
	data->temp1 = vector_sub(&ray->start, &data->cylinder[current].pos);
	data->temp3 = dot_product(&data->temp1, &data->cylinder[current].axis);
	data->b = 2 * (data->temp2 * data->temp3 - (dot_product(&ray->dir, \
	&data->temp1)));
	data->c = pow(data->temp3, 2) - dot_product(&data->temp1, &data->temp1) \
	+ pow(data->cylinder[current].radius, 2) ;
	data->discr = data->b * data->b - 4 * data->a * data->c;
	if (data->discr < 0)
		return (0);
	data->t0 = ((-data->b + sqrt(data->discr)) / 2 * data->a);
	data->t1 = ((-data->b - sqrt(data->discr)) / 2 * data->a);
	if (data->t0 > data->t1)
		data->t0 = data->t1;
	if (data->t0 > 0 && data->t0 < *t)
	{
		*t = data->t0;
		return (1);
	}
	return (0);
}
