/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:17:21 by lstepany          #+#    #+#             */
/*   Updated: 2021/04/08 00:17:22 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	data->ratio = WIDTH / HEIGHT;
	while (data->y < HEIGHT)
	{
		data->x = 0;
		while (data->x < WIDTH)
		{
			data->v_up = vector_scale(-(2 * (float)data->y / HEIGHT - 1) *  \
			tan(convert_radian(FOV / 2)), &data->cam.up);
			data->v_right = vector_scale((2 * (float)data->x / WIDTH - 1) * \
			tan(convert_radian(FOV / 2)) * data->ratio, &data->cam.right);
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
		put_message("allocation failed at 'data'");
	if (argc != 2)
		put_message("The number of arguments must be one");
	if (!(data->fd = open(argv[1], O_RDONLY)) && data->fd == -1)
		put_message("file opening error");
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
