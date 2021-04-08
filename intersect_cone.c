/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:16:26 by lstepany          #+#    #+#             */
/*   Updated: 2021/04/08 00:16:27 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vector	rotate(t_data *data, int current)
{
	data->cone[current].axis = data->vertical;
	data->cone[current].axis = rot_x(data->cone[current].axis, \
	data->cone[current].cone_rot_x[current]);
	data->cone[current].axis = rot_y(data->cone[current].axis, \
	data->cone[current].cone_rot_y[current]);
	data->cone[current].axis = rot_z(data->cone[current].axis, \
	data->cone[current].cone_rot_z[current]);
	return(data->cone[current].axis);
}

int		intersect_ray_cone(t_data *data, t_ray *ray, int current, float *t)
{
	if (!data->cone || (data->cone_count - 1) < current)
		return (0);
	data->cone[current].axis = rotate(data, current);
	data->temp2 = dot_product(&ray->dir, &data->cone[current].axis);
	data->a = pow(data->temp2, 2) - pow(cos(convert_radian(CONE)), 2);
	data->temp1 = vector_sub(&ray->start, &data->cone[current].pos);
	data->temp3 = dot_product(&data->temp1, &data->cone[current].axis);
	data->b = 2 * (data->temp2 * data->temp3 - (dot_product(&ray->dir, \
	&data->temp1) * pow(cos(convert_radian(CONE)), 2)));
	data->c = pow(data->temp3, 2) - dot_product(&data->temp1, &data->temp1) * \
	pow(cos(convert_radian(CONE)), 2);
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
