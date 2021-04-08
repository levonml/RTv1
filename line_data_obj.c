/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_data_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:17:00 by lstepany          #+#    #+#             */
/*   Updated: 2021/04/08 00:17:01 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	line_data_sphere(t_data *data)
{
	if (!data->sphere_check)
	{
		data->sphere_check = 1;
		data->sphere_num = ft_atoi(data->split[1]);
		data->sphere = allocate(data->sphere, data->sphere_num);
	}
	else
	{
		fill_data(data->sphere, data, data->sphere_count);
		data->sphere_count++;
	}
}

void	line_data_cone(t_data *data)
{
	if (!data->cone_check)
	{
		data->cone_check = 1;
		data->cone_num = ft_atoi(data->split[1]);
		data->cone = allocate(data->cone, data->cone_num);
	}
	else
	{
		fill_data(data->cone, data, data->cone_count);
		data->cone_count++;
	}
}

void	line_data_cylinder(t_data *data)
{
	if (!data->cylinder_check)
	{
		data->cylinder_check = 1;
		data->cylinder_num = ft_atoi(data->split[1]);
		data->cylinder = allocate(data->cylinder, data->cylinder_num);
	}
	else
	{
		fill_data(data->cylinder, data, data->cylinder_count);
		data->cylinder_count++;
	}
}

void	line_data_plane(t_data *data)
{
	if (!data->plane_check)
	{
		data->plane_check = 1;
		data->plane_num = ft_atoi(data->split[1]);
		data->plane = allocate(data->plane, data->plane_num);
	}
	else
	{
		fill_data(data->plane, data, data->plane_count);
		data->plane_count++;
	}
}
