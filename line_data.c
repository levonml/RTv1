/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:17:12 by lstepany          #+#    #+#             */
/*   Updated: 2021/04/08 00:17:13 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	line_data_light(t_data *data)
{
	if (!data->light_check)
	{
		data->light_check = 1;
		data->light_num = ft_atoi(data->split[1]);
		data->light = allocate(data->light, data->light_num);
	}
	else
	{
		fill_data(data->light, data, data->light_count);
		data->light_count++;
	}
}

void	line_data_camera(t_data *data)
{
	data->camera = allocate(data->camera, 1);
	fill_data(data->camera, data, 0);
}
