/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstepany <lstepany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 00:18:03 by lstepany          #+#    #+#             */
/*   Updated: 2021/04/08 00:18:05 by lstepany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RT_H
# define RT_H
# define RED 150
# define BLUE 200
# define GREEN 150
# define WIDTH  1800
# define HEIGHT 900
# define FOV 10
# define CONE 20
# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
	t_vector	up;
	t_vector	right;
	float		screen_dist;
}				t_ray;
typedef struct	s_light
{
	t_vector	pos;
}				t_light;
typedef struct	s_shape
{
	t_vector	pos;
	t_vector	normal;
	t_vector	dir;
	t_vector	axis;
	float		radius;
	float		sphere_rot_x[20];
	float		sphere_rot_y[20];
	float		sphere_rot_z[20];
	float		cylinder_rot_x[20];
	float		cylinder_rot_y[20];
	float		cylinder_rot_z[20];
	float		plane_rot_x[20];
	float		plane_rot_y[20];
	float		plane_rot_z[20];
	float		cone_rot_x[20];
	float		cone_rot_y[20];
	float		cone_rot_z[20];
	int			r;
	int			b;
	int			g;
}				t_shape;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	void		*image;
	char		*buffer;
	char		*str;
	char		**split;
	int			fd;
	int			pixel_bits;
	int			line_bytes;
	int			endian;
	int			obj_num;
	int			iter_light;
	int			i_cylinder;
	int			i_sphere;
	int			i_cone;
	int			i_plane;
	int			iter;
	int			intersect;
	int			in_shadow;
	int			x;
	int			y;
	int			pixel;
	int			count;
	int			num;
	int			current_light;
	int			sphere_value;
	int			cylinder_value;
	int			sphere_count;
	int			cylinder_count;
	int			light_count;
	int			cone_count;
	int			plane_count;
	int			cone_num;
	int			sphere_num;
	int			plane_num;
	int			cylinder_num;
	int			cylinder_exist;
	int			light_num;
	int			sphere_check;
	int			cylinder_check;
	int			cone_check;
	int			light_check;
	int			plane_check;
	int			split_count;
	float		red;
	float		green;
	float		blue;
	float		visible;
	float		t;
	float		light_t;
	float		sphere_t;
	float		cylinder_t;
	float		cone_t;
	float		temp;
	float		lambert;
	float		discr;
	float		ratio;
	float		a;
	float		b;
	float		c;
	float		t0;
	float		t1;
	float		u;
	float		temp2;
	float		temp3;
	t_shape		*sphere;
	t_shape		*cylinder;
	t_shape		*cone;
	t_shape		*plane;
	t_shape		*light;
	t_shape		*camera;
	t_vector	v_up;
	t_vector	v_right;
	t_vector	r_up;
	t_vector	dist;
	t_vector	scaled;
	t_vector	new_start;
	t_vector	n;
	t_vector	vertical;
	t_vector	center;
	t_vector	temp1;
	t_vector	v_temp;
	t_ray		r;
	t_ray		light_ray;
	t_ray		cam;
}				t_data;

int				intersect_ray_sphere(t_data *data, t_ray *ray, int i, float *t);
int				intersect_ray_cylinder(t_data *data, t_ray *ray, int i, \
float *t);
int				intersect_ray_cone(t_data *data, t_ray *ray, int i, float *t);
int				intersect_ray_plane(t_data *data, t_ray *ray, int i, float *t);
int				key_control(int key);
int				expose_hook(void *d);
int				cylinder(t_data *data, int i);
int				cone(t_data *data, int i);
int				sphere(t_data *data, int i);
int				plane(t_data *data, int i);
int				compere(t_ray r1, t_ray r2);
int				find_intersection(t_data *data, t_ray *ray, int i, float *t);
int				max_num(int a, int b, int c, int d);
float			ft_abs(float t);
float			dot_product(t_vector *v1, t_vector *v2);
float			dot_product_xz(t_vector v1, t_vector v2);
float			dot_product_xy(t_vector *v1, t_vector *v2);
float			ft_abs(float t);
float			convert_radian(float a);
void			render(t_data *data);
void				data_init(t_data *data);
void			find_cylinders(t_data *data, t_ray *r, int current_obj, \
float *t);
void			find_cones(t_data *data, t_ray *r, int current_obj, float *t);
void			find_spheres(t_data *data, t_ray *r, int current_obj, float *t);
void			find_planes(t_data *data, t_ray *r, int current_obj, float *t);
void			line_data_sphere(t_data *data);
void			line_data_cylinder(t_data *data);
void			line_data_cone(t_data *data);
void			line_data_plane(t_data *data);
void			line_data_light(t_data *data);
void			fill_data(t_shape *shape, t_data *data, int i);
void			line_data_camera(t_data *data);
void			put_message(char *str);
t_vector		vector_add(t_vector *v1, t_vector *v2);
t_vector		vector_sub(t_vector *v1, t_vector *v2);
t_vector		vector_scale(float a, t_vector *v);
t_vector		vector_sub_xz(t_vector *v1, t_vector *v2);
t_vector		vector_add_xz(t_vector *v1, t_vector *v2);
t_vector		vector_scale_xz(float a, t_vector *v);
t_vector		rot_y(t_vector v, float a);
t_vector		rot_z(t_vector v, float a);
t_vector		rot_x(t_vector v, float a);
t_vector		cross_product(t_vector v1, t_vector v2);
t_vector		normalize(t_vector v);
t_shape			*allocate(t_shape *shape, int num);

#endif
