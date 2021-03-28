#include "rt.h"

static void	choose_color(t_data *data, int current_plane)
{
	data->lambert = dot_product(&data->light_ray.dir, \
	&data->plane[current_plane].normal);
	data->lambert = ft_abs(data->lambert);
	data->blue += data->plane[current_plane].b * data->lambert;
	if (data->blue > 255)
		data->blue = 255;
	data->green += data->plane[current_plane].g * data->lambert;
	if (data->green > 255)
		data->green = 255;
	data->red += data->plane[current_plane].r * data->lambert;
	if (data->red > 255)
		data->red = 255;
}

static void	get_new_ray(t_data *data, int current_plane)
{
	data->light_ray.start = data->new_start;
	data->light_ray.dir = vector_scale(1 / data->light_t, &data->dist);
	data->in_shadow = 0;
	data->count = 0;
	while (data->count < data->obj_num)
	{
		if (find_intersection(data, &data->light_ray, \
		data->count, &data->light_t))
		{
			data->in_shadow = 1;
			break ;
		}
		data->count++;
	}
	if (!data->in_shadow)
		choose_color(data, current_plane);
}

int			calculate(t_data *data, int current_plane)
{
	data->scaled = vector_scale(data->t, &data->r.dir);
	data->new_start = vector_add(&data->r.start, &data->scaled);
	data->temp = dot_product(&data->plane[current_plane].normal, \
	&data->plane[current_plane].normal);
	if (data->temp == 0)
		return (0);
	data->temp = 1 / sqrt(data->temp);
	data->plane[current_plane].normal = vector_scale(data->temp, \
	&data->plane[current_plane].normal);
	data->current_light = 0;
}

int			plane(t_data *data, int current_plane, int i)
{
	if (!calculate(data, current_plane))
		return (0);
	while (data->current_light < data->light_num)
	{
		data->dist = \
		vector_sub(&data->light[data->current_light].pos, &data->new_start);
		if (dot_product(&data->dist, &data->plane[current_plane].normal) != 0)
		{
			data->light_t = sqrt(dot_product(&data->dist, &data->dist));
			if (data->light_t > 0)
				get_new_ray(data, current_plane);
		}
		data->current_light++;
	}
	return (0);
}
