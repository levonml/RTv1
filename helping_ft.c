#include "rt.h"

int		max_num(int a, int b, int c, int d)
{
	if (a < b)
		a = b;
	if (a < c)
		a = c;
	if (a < d)
		a = d;
	return (a);
}

float	ft_abs(float t)
{
	if (t < 0)
		return (-t);
	return (t);
}

void	put_message(char *str)
{
	ft_putstr(str);
	exit(0);
}

t_shape	*allocate(t_shape *shape, int num)
{
	if (!(shape = (t_shape *)malloc(sizeof(t_shape) * num)))
		exit(0);
	return (shape);
}