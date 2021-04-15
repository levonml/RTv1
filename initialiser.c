/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:16:20 by lstepany          #+#    #+#             */
/*   Updated: 2021/04/08 00:16:21 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void erase(void **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		ft_memdel(&split[i]);
		i++;
	}
	free(split);
	split = NULL;
}
void	pars_plane(t_shape *shape, t_data *data, int i)
{
	shape[i].pos.x = ft_atoi(data->split[2]);// + WIDTH / 2;
	shape[i].pos.y = ft_atoi(data->split[3]);// + HEIGHT / 2;
	shape[i].pos.z = ft_atoi(data->split[4]);
	shape[i].normal.x = ft_atoi(data->split[6]);
	shape[i].normal.y = ft_atoi(data->split[7]);
	shape[i].normal.z = ft_atoi(data->split[8]);
	shape[i].r = ft_atoi(data->split[11]);
	shape[i].g = ft_atoi(data->split[13]);
	shape[i].b = ft_atoi(data->split[15]);
	shape[i].plane_rot_x[i] = ft_atoi(data->split[17]);
	shape[i].plane_rot_y[i] = ft_atoi(data->split[18]);
	shape[i].plane_rot_z[i] = ft_atoi(data->split[19]);
}

void	camera_pars(t_shape *shape, t_data *data, int i)
{
	shape[i].pos.x = ft_atoi(data->split[2]);// + WIDTH / 2;
	shape[i].pos.y = ft_atoi(data->split[3]);// + HEIGHT / 2;
	shape[i].pos.z = ft_atoi(data->split[4]);
	data->center.x = ft_atoi(data->split[6]);// + WIDTH / 2;
	data->center.y = ft_atoi(data->split[7]);// + HEIGHT / 2;
	data->center.z = ft_atoi(data->split[8]);
	data->cam.up.x = 0;
	data->cam.up.y = -1;
	data->cam.up.z = 0;
}

void	first_value(t_data *data)
{
	data->sphere_count = 0;
	data->cylinder_count = 0;
	data->light_count = 0;
	data->plane_count = 0;
	data->cone_count = 0;
	data->sphere_check = 0;
	data->cylinder_check = 0;
	data->cone_check = 0;
	data->light_check = 0;
	data->plane_check = 0;
	data->cone_num = 0;
	data->sphere_num = 0;
	data->cylinder_num = 0;
	data->plane_num = 0;
	data->cylinder = NULL;
	data->sphere = NULL;
	data->cone = NULL;
	data->y = 0;
	data->blue = 0;
	data->green = 0;
	data->red = 0;
	data->vertical.x = 0;	
	data->vertical.y = 1;
	data->vertical.z = 0;
}

void	fill_data(t_shape *shape, t_data *data, int i)
{
	if (ft_strcmp(data->split[0], "camera") == 0)
		camera_pars(shape, data, i);
	if (ft_strcmp(data->split[0], "plane") == 0)
	{
		if (data->split_count < 18)
			put_message("wrong structure of line plane in the argument file");
		pars_plane(shape, data, i);
	}
	if (ft_strcmp(data->split[0], "sphere") == 0)
	{
		if (data->split_count < 10)
			put_message("wrong structure of line sphere in the argument file");
		shape[i].pos.x = ft_atoi(data->split[2]);// + WIDTH / 2;
		shape[i].pos.y = ft_atoi(data->split[3]);// + HEIGHT / 2;
		shape[i].pos.z = ft_atoi(data->split[4]);
		shape[i].radius = ft_atoi(data->split[6]);
		shape[i].sphere_rot_x[i] = ft_atoi(data->split[8]);
		shape[i].sphere_rot_y[i] = ft_atoi(data->split[9]);
		shape[i].sphere_rot_z[i] = ft_atoi(data->split[10]);
	}
	if (ft_strcmp(data->split[0], "cylinder") == 0)
	{
		if (data->split_count < 10)
			put_message("wrong structure of line cylinder in the argument file");
		shape[i].radius = ft_atoi(data->split[6]);
		shape[i].cylinder_rot_x[i] = ft_atoi(data->split[8]);
		shape[i].cylinder_rot_y[i] = ft_atoi(data->split[9]);
		shape[i].cylinder_rot_z[i] = ft_atoi(data->split[10]);
		shape[i].pos.x = ft_atoi(data->split[2]);// + WIDTH / 2;
		shape[i].pos.y = ft_atoi(data->split[3]);// + HEIGHT / 2;
		shape[i].pos.z = ft_atoi(data->split[4]);
	}
	if (ft_strcmp(data->split[0], "cone") == 0)
	{
		shape[i].radius = ft_atoi(data->split[6]);
		shape[i].cone_rot_x[i] = ft_atoi(data->split[8]);
		shape[i].cone_rot_y[i] = ft_atoi(data->split[9]);
		shape[i].cone_rot_z[i] = ft_atoi(data->split[10]);
		shape[i].pos.x = ft_atoi(data->split[2]);// + WIDTH / 2;
		shape[i].pos.y = ft_atoi(data->split[3]);// + HEIGHT / 2;
		shape[i].pos.z = ft_atoi(data->split[4]);
	}
	if (ft_strcmp(data->split[0], "light") == 0)
	{
		if (data->split_count != 5)
			put_message("wrong structure of line light in the argument file");
		shape[i].pos.x = ft_atoi(data->split[2]);// + WIDTH / 2;
		shape[i].pos.y = ft_atoi(data->split[3]);// + HEIGHT / 2;
		shape[i].pos.z = ft_atoi(data->split[4]);	
	}
}

void	data_init(t_data *data)
{
	first_value(data);
	while (get_next_line(data->fd, &data->str) == 1)
	{
		if(data->str[0] != '\0')
		{
			if (!(data->split = ft_strsplit(data->str, ' ')))
				put_message("malloc error in ft_strsplit");
			data->split_count = 0;
			while (data->split[data->split_count])
				data->split_count++;
			if (ft_strcmp(data->split[0], "camera") == 0)
				line_data_camera(data);
			else if (ft_strcmp(data->split[0], "sphere") == 0)
				line_data_sphere(data);
			else if (ft_strcmp(data->split[0], "cone") == 0)
				line_data_cone(data);
			else if (ft_strcmp(data->split[0], "cylinder") == 0)
				line_data_cylinder(data);
			else if (ft_strcmp(data->split[0], "plane") == 0)
				line_data_plane(data);
			else if (ft_strcmp(data->split[0], "light") == 0)
				line_data_light(data);
			erase((void **)data->split);
		}
		ft_memdel((void **)&data->str);
	}
}
