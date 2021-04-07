/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:18:14 by lstepany          #+#    #+#             */
/*   Updated: 2021/04/08 00:18:15 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"

static void	choose_color(t_data *data)
{
	data->lambert = dot_product(&data->light_ray.dir, &data->n);
	data->blue = 0;
	data->green = 0;
	data->red += RED * data->lambert;
	if (data->red > 255)
		data->red = 255;
}

static void	get_new_ray(t_data *data)
{
	data->light_ray.start = data->new_start;
	data->light_ray.dir = normalize(data->dist);
	data->in_shadow = 0;
	data->count = 0;
	while (data->count < data->obj_num)
	{
		if (find_intersection(data, &data->light_ray, data->count, \
		&data->light_t))
		{
			data->in_shadow = 1;
			break ;
		}
		data->count++;
	}
	if (!data->in_shadow)
		choose_color(data);
}

//int			sphere(t_data *data, int current_sphere, int i)
int			sphere(t_data *data, int current_sphere)

{
	data->scaled = vector_scale(data->t, &data->r.dir);
	data->new_start = vector_add(&data->r.start, &data->scaled);
	data->n = normalize(vector_sub(&data->new_start, \
	&data->sphere[current_sphere].pos));
	data->current_light = 0;
	while (data->current_light < data->light_num)
	{
		data->dist = vector_sub(&data->light[data->current_light].pos, \
		&data->new_start);
		if (dot_product(&data->dist, &data->n) > 0)
		{
			data->light_t = sqrt(dot_product(&data->dist, &data->dist));
			if (data->light_t > 0)
				get_new_ray(data);
		}
		data->current_light++;
			//ft_putstr("ddddd");
	}
	//choose_color(data);
	return (1);
}
