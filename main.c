#include "rt.h"



int compere(t_ray r1, t_ray r2)
{
	if(r1.start.x == r2.start.x && r1.start.y == r2.start.y && r1.start.z == r2.start.z)
		return(1);
	return(0);
}
int		find_intersection(t_data *data, t_ray *ray, int current_obj, float *t)
{
	data->intersect = 0;
	data->visible = *t;
	if (current_obj < data->cylinder_num)
		find_cylinders(data, ray, current_obj, t);
	if (current_obj < data->sphere_num)
		find_spheres(data, ray, current_obj, t);
	if (current_obj < data->cone_num)
		find_cones(data, ray, current_obj, t);
	if (current_obj < data->plane_num && compere(*ray, data->r))
		find_planes(data, ray, current_obj, t);
	return (data->intersect);
}

int		iterate_over_objects(t_data *data)
{
	if (data->i_sphere != -1)
	{
		if (!sphere(data, data->i_sphere))
			return (0);
	}
	else if (data->i_cylinder != -1)
	{
		if (!cylinder(data, data->i_cylinder))
			return (0);
	}
	else if (data->i_cone != -1)
	{
		if (!cone(data, data->i_cone))
			return (0);
	}
	else if (data->i_plane != -1)
	{
		if (!plane(data, data->i_plane))
			return (0);
	}
	return (1);
}

void	iter_over_x(t_data *data)
{
	data->t = 500000;
	data->iter = 0;
	data->i_cylinder = -1;
	data->i_sphere = -1;
	data->i_cone = -1;
	data->i_plane = -1;
	data->red = 0;
	data->green = 0;
	data->blue = 0;
	while (data->iter < data->obj_num)
	{
		find_intersection(data, &data->r, data->iter, &data->t);
		data->iter++;
	}
	iterate_over_objects(data);
	data->pixel = data->y * data->line_bytes + data->x * 4;
	data->buffer[data->pixel + 0] = data->blue;
	data->buffer[data->pixel + 1] = data->green;
	data->buffer[data->pixel + 2] = data->red;
	data->buffer[data->pixel + 3] = 0;
}
t_vector	multiply_x(float a, t_vector v)
{
	v.x = v.x * a;
	//v.y = 0;
	//v.z = 0;
	return (v);
}
t_vector	multiply_y(float a, t_vector v)
{
	v.y = v.y * a;
	//v.x = 0;
	//v.z = 0;
	return (v);
}
void	render(t_data *data)
{
	if (!data->camera)
		put_message("camera is missing");
	data->obj_num = max_num(data->cone_num, data->cylinder_num,\
	data->sphere_num, data->plane_num);
	data->cam.dir = normalize(vector_sub(&data->center, &data->camera[0].pos));
	data->cam.right = normalize(cross_product(data->cam.dir, data->cam.up));
	data->cam.up = normalize(cross_product(data->cam.right, data->cam.dir));
	data->r.start = data->camera[0].pos;
	float ratio = WIDTH / HEIGHT;
	while (data->y < HEIGHT)
	{
		data->x = 0;
		while (data->x < WIDTH)
		{
			//float nds_x = (data->x + 0.5) / WIDTH;
			//float nds_y = (data->y + 0.5) / HEIGHT;
			//float screen_x = 2 * nds_x - 1;
			//float screen_y = 1 - 2 * nds_y;
			//float xx = (2 * screen_x - 1) * ratio * tan(convert_radian(FOV/2));
			//float yy = (1 - 2 * screen_y) * tan(convert_radian(FOV/2));
			//float yy = -(2 * ((float)data->y + 0.5) / (HEIGHT) - 1) * tan(convert_radian(FOV/12));
			//float xx =  (2 * ((float)data->x + 0.5) / (WIDTH)- 1) * ratio * tan(convert_radian(FOV/12));
			//data->v_up = multiply_y(yy, data->cam.up);
			//data->v_right = multiply_x(xx, data->cam.right);
			data->v_up =   vector_scale(-(2 * (float)data->y / HEIGHT - 1) *  tan(convert_radian(FOV/2)) , &data->cam.up);
			data->v_right = vector_scale((2 * (float)data->x / WIDTH - 1) * tan(convert_radian(FOV/2)) * ratio , &data->cam.right);
			data->r_up = (vector_add(&data->v_up, &data->v_right));
			data->r.dir = normalize(vector_add(&data->r_up, &data->cam.dir));
			iter_over_x(data);
			data->x++;
		}
		data->y++;
	}
}

int		main(int argc, char **argv)
{
	t_data	*data;

	if (!(data = malloc(sizeof(t_data))))
		return (0);
	if (argc != 2)
	{
		ft_putstr("The number of arguments should be one");
		return (0);
	}
	if (!(data->fd = open(argv[1], O_RDONLY)) && data->fd == -1)
	{
		ft_putstr("file opening error");
		return (0);
	}
	data_init(data);
	close(data->fd);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "RT");
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->buffer = mlx_get_data_addr(data->image, &data->pixel_bits,\
	&data->line_bytes, &data->endian);
	mlx_key_hook(data->win, key_control, data);
	mlx_expose_hook(data->win, expose_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
