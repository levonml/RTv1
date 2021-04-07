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

int		intersect_ray_cylinder(t_data *data, t_ray *ray, int current, float *t)
{
	if (!data->cylinder || (data->cylinder_count - 1) < current)
		return (0);
	
	//data->cylinder[current].axis.x = 0;
	//data->cylinder[current].axis.y = 1;
	//data->cylinder[current].axis.z = 0;
	
	data->cylinder[current].axis = rot_z(data->vertical, data->cylinder[current].cylinder_rot[current]);
	//v = rot_y(v, 80);
	t_vector co;
	float dv = dot_product(&ray->dir, &data->cylinder[current].axis);
	data->a = pow(dv, 2) - 1;
	co = vector_sub(&ray->start, &data->cylinder[current].pos);
	float cov = dot_product(&co, &data->cylinder[current].axis);
	data->b = 2 * (dv * cov - (dot_product(&ray->dir, &co)));
	data->c = pow(cov, 2) - dot_product(&co, &co) + pow(data->cylinder[current].radius, 2) ;
	data->discr = data->b * data->b - 4 * data->a * data->c;
	if (data->discr < 0)
		return (0);
	else
	{
		data->t0 = ((-data->b + sqrt(data->discr)) / 2 * data->a);
		data->t1 = ((-data->b - sqrt(data->discr)) / 2 * data->a);
		if (data->t0 > data->t1)
			data->t0 = data->t1;
		if (data->t0 > 0 && data->t0 < *t)
		{
			*t = data->t0;
			return (1);
		}
	}
	return (0);
}
