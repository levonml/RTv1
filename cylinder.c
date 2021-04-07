#include "rt.h"

static void	choose_color(t_data *data)
{
	data->lambert = dot_product(&data->light_ray.dir, &data->n);
	data->blue = 0;
	data->green += (GREEN) * data->lambert;
	if (data->green > 255)
		data->green = 255;
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
		//data->light_t = 4000000;
		if (find_intersection(data, &data->light_ray,\
		data->count, &data->light_t))
		{
			data->in_shadow = 1;
			break ;
		}
		data->count++;
	}
	if (data->in_shadow == 0)
		choose_color(data);      
}

//int		cylinder(t_data *data, int current_cylinder, int i)
int		cylinder(t_data *data, int current_cylinder)
{
	//v = rot_z(v, 30);
	/*data->scaled = vector_scale(data->t, &data->r.dir);
	data->new_start = vector_add(&data->r.start, &data->scaled);
	//data->cylinder[current_cylinder].pos.y = data->new_start.y;
	t_vector d = data->cylinder[current_cylinder].pos;
	d.y = data->new_start.y;
	//data->cylinder[current_cylinder].pos = d;
	data->n = normalize(vector_sub_xz(&data->new_start, &d));*/
	
	/*t_vector temp = vector_sub(&data->r.start, &data->cylinder[current_cylinder].pos);
	float m = dot_product(&data->r.dir, &v) * data->t + dot_product(&temp, &v);
	data->scaled = vector_scale(data->t, &data->r.dir);
	data->new_start = vector_add(&data->r.start, &data->scaled);
	t_vector t = vector_scale(m, &v);
	data->n = vector_sub(&data->new_start, &data->cylinder[current_cylinder].pos);
	data->n = vector_sub(&data->n, &t);
	data->n = normalize(data->n);*/

	data->scaled = vector_scale(data->t, &data->r.dir);
	data->new_start = vector_add(&data->r.start, &data->scaled);
	t_vector temp = vector_sub(&data->new_start, &data->cylinder[current_cylinder].pos);
	float m = dot_product(&temp, &data->cylinder[current_cylinder].axis);
	t_vector mm = vector_scale(m, &data->cylinder[current_cylinder].axis);
	data->n = normalize(vector_sub(&temp, &mm));


	//printf("n.y = %f\n", data->n.z);
	data->current_light = 0;
	while(data->current_light < data->light_num)
	{
		//data->light[data->current_light].pos.y = data->y;
		data->dist = vector_sub(&data->light[data->current_light].pos, &data->new_start);
		if( dot_product(&data->dist, &data->n) > 0 )
		{
			data->light_t = sqrt(dot_product(&data->dist, &data->dist));
			if (data->light_t > 0)
				get_new_ray(data);
		}
		data->current_light++;
	}
	//choose_color(data);
  	return(1);
}
