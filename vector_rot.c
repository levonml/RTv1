#include "rt.h"

float		convert_radian(float a)
{
	float	pi;

	pi = 22 / 7;
	return (a * pi / 180);
}

t_vector	normalize(t_vector v)
{
	float	temp;
	float	dot;

	dot = dot_product(&v, &v);
	if (dot > 0)
		temp = 1 / sqrt(dot_product(&v, &v));
	return (vector_scale(temp, &v));
}

t_vector	rot_z(t_vector v, float a)
{
	float	rad;
	float	x;

	rad = convert_radian(a);
	x = v.x;
	v.x = (v.x * cosf(rad) - v.y * sin(rad));
	v.y = (x * sinf(rad) + v.y * cos(rad));
	v.z = v.z;
	return (v);
}

t_vector	rot_y(t_vector v, float a)
{
	float	rad;
	float	x;

	rad = convert_radian(a);
	x = v.x;
	v.x = (v.z * sinf(rad) + v.x * cosf(rad));
	v.z = (v.z * cosf(rad) - x * sinf(rad));
	v.y = v.y;
	return (v);
}
