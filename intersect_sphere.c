
#include "rt.h"

int	intersect_ray_sphere(t_data *data, t_ray *ray, int current, float *t)
{
	if (!data->sphere || (data->sphere_count - 1) < current)
		return (0);
	data->a = dot_product(&ray->dir, &ray->dir);
	data->dist = vector_sub(&ray->start, &data->sphere[current].pos);
	data->b = 2 * dot_product(&ray->dir, &data->dist);
	data->c = dot_product(&data->dist, &data->dist) - \
	pow(data->sphere[current].radius, 2);
	data->discr = data->b * data->b - 4 * data->a * data->c;
	if (data->discr <= 0)
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
