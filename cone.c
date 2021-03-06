/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:15:29 by lstepany          #+#    #+#             */
/*   Updated: 2021/04/08 00:15:34 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		choose_color(t_data *data)
{
	data->lambert = dot_product(&data->light_ray.dir, &data->n);
	data->blue += BLUE * data->lambert;
	if (data->blue > 255)
		data->blue = 255;
	data->green = 0;
	data->red = 0;
}

static void	get_new_ray(t_data *data)
{
	data->light_ray.start = data->new_start;
	data->light_ray.dir = normalize(data->dist);
	data->in_shadow = 0;
	data->count = 0;
	while (data->count < data->obj_num)
	{
		if (find_intersection(data, &data->light_ray,\
		data->count, &data->light_t))
		{
			data->in_shadow = 1;
			break ;
		}
		data->count++;
	}
	if (!data->in_shadow)
		choose_color(data);
}

int			cone(t_data *data, int current)
{
	data->scaled = vector_scale(data->t, &data->r.dir);
	data->new_start = vector_add(&data->r.start, &data->scaled);
	data->n = vector_sub(&data->new_start, &data->cone[current].pos);
	data->v_temp = vector_scale(dot_product(&data->n, \
	&data->cone[current].axis), &data->cone[current].axis);
	data->n = normalize(vector_sub(&data->n, &data->v_temp));
	data->current_light = 0;
	while (data->current_light < data->light_num)
	{
		data->dist = vector_sub(&data->light[data->current_light].pos,\
		&data->new_start);
		if (dot_product(&data->dist, &data->n) > 0)
		{
			data->light_t = sqrt(dot_product(&data->dist, &data->dist));
			if (data->light_t > 0)
				get_new_ray(data);
		}
		data->current_light++;
	}
	return (1);
}
