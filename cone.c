#include "rt.h"

void		choose_color(t_data *data)
{
	data->lambert = dot_product(&data->light_ray.dir, &data->n);
	//data->lambert = abs(data->lambert);
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

//int			cone(t_data *data, int current_cone, int i)
int			cone(t_data *data, int current_cone)

{
	/*data->scaled = vector_scale(data->t, &data->r.dir);
	data->new_start = vector_add(&data->r.start, &data->scaled);
	//data->cone[current_cone].pos.y = data->new_start.y;
	t_vector temp = data->cone[current_cone].pos;
	temp.y = data->new_start.y;
	data->n = vector_sub(&data->new_start, &temp);
	//data->n.y += dot_product(&data->n, &data->n) * tan(convert_radian(CONE));
	data->n = normalize(data->n);*/
	data->scaled = vector_scale(data->t, &data->r.dir);
	data->new_start = vector_add(&data->r.start, &data->scaled);
	t_vector temp = vector_sub(&data->new_start, &data->cone[current_cone].pos);
	float m = dot_product(&temp, &data->cone[current_cone].axis);
	t_vector mm = vector_scale(m, &data->cone[current_cone].axis);
	data->n = normalize(vector_sub(&temp, &mm));
	
	
	data->current_light = 0;
	while (data->current_light < data->light_num)
	{
		data->dist = vector_sub(&data->light[data->current_light].pos,\
		&data->new_start);
		t_vector d = normalize(data->dist);
		//t_vector t = normalize(data->temp);
		if (dot_product(&d, &data->n) > 0)
		{
			data->light_t = sqrt(dot_product(&data->dist, &data->dist));
			if (data->light_t > 0)
				get_new_ray(data);
		}
		data->current_light++;
	}
	//choose_color(data);
	return (1);
}
