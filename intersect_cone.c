#include "rt.h"

int		intersect_ray_cone(t_data *data, t_ray *ray, int current, float *t)
{
	if (!data->cone || (data->cone_count - 1) < current)
		return (0);
	//data->cone.axis.x = 0;
	//data->cone.axis.y = 1;
	//data->cone.axis.z = 0;
	//data->cone.axis = rot_z(v, 30);
	data->cone[current].axis = rot_z(data->vertical, data->cone[current].cone_rot[current]);

	t_vector co;
	float dv = dot_product(&ray->dir, &data->cone[current].axis);
	data->a = pow(dv, 2) - pow(cos(convert_radian(CONE)), 2);
	co = vector_sub(&ray->start, &data->cone[current].pos);
	float cov = dot_product(&co, &data->cone[current].axis);
	data->b = 2 * (dv * cov - (dot_product(&ray->dir, &co) * pow(cos(convert_radian(CONE)), 2)));
	data->c = pow(cov, 2) - dot_product(&co, &co) * pow(cos(convert_radian(CONE)), 2);
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
		//t_vector scaled = vector_scale(*t, &ray->dir);
		//t_vector t = vector_sub(&scaled, &data->cone[current].pos);
		//if(dot_product(&t, &v) < 0)
			return (1);
	}
	return (0);
}
