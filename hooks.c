/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:16:13 by lstepany          #+#    #+#             */
/*   Updated: 2021/04/08 00:16:14 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		key_control(int key)
{
	if (key == 65307)
		exit(0);
	return (0);
}

int		expose_hook(void *d)
{
	t_data	*data;

	data = (t_data *)d;
	render(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
	return (0);
}
