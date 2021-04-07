/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_xz.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:18:31 by lstepany          #+#    #+#             */
/*   Updated: 2021/04/08 00:18:32 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"

float		dot_product_xz(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.z * v2.z);
}

float		dot_product_xy(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y);
}

t_vector	vector_scale_xz(float a, t_vector *v)
{
	t_vector	res;

	res.x = (v->x) * (a);
	res.z = (v->z) * (a);
	return (res);
}

t_vector	vector_sub_xz(t_vector *v1, t_vector *v2)
{
	t_vector	res;


	res.x = v1->x - v2->x;
	res.z = v1->z - v2->z;
	res.y = 0;
	return (res);
}

t_vector	vector_add_xz(t_vector *v1, t_vector *v2)
{
	t_vector	res;

	res.x = v1->x + v2->x;
	res.z = v1->z + v2->z;
	return (res);
}
