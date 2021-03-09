#ifndef RT_H
# define RT_H
#include "libft/libft.h"
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define RED 150
#define BLUE 150
#define GREEN 150
#define WIDTH  1800
#define HEIGHT 800

typedef struct  s_vector
{
    float x;
    float y;
    float z;
}               t_vector;

typedef struct  s_ray
{
    t_vector start;
    t_vector dir;
}               t_ray;

typedef struct  s_light
{
    t_vector pos;
}               t_light;

typedef struct  s_shape
{
    t_vector    pos;
    float       radius;
}               t_shape;

typedef struct s_data
{
    void	*mlx;
    void	*win;
    void	*image;
    char	*buffer;
    char    *str;
    int     fd;
    int	    pixel_bits;
    int     line_bytes;
    int     endian;
    int     x;
    int     y;
    float   red;
    float   green;
    float   blue;
    int     pixel;
    float   t;
    float   sphere_t;
    float   cylinder_t;
    float   cone_t;
    float   temp;
    float   lambert;
    int     sphere_value;
    int     cylinder_value;
    int     cone_count;
    int     cone_num;
    int     sphere_num;
    int     cylinder_num;
    int     light_num;
    t_shape *sphere;
    t_shape *cylinder;
    t_shape *cone;
    t_shape *light;
    t_ray       r;
    t_ray       light_ray;
   // t_light     light;
    t_vector    dist;
    t_vector scaled;
    t_vector new_start;
    t_vector n;
}               t_data;

int         intersect_ray_sphere(t_data *data, int i);
int         intersect_ray_cylinder(t_data *data, int i);
int         intersect_ray_cone(t_data *data, int i);
t_vector    vector_add(t_vector *v1, t_vector *v2);
t_vector    vector_sub(t_vector *v1, t_vector *v2);
float       dot_product(t_vector *v1, t_vector *v2);
t_vector    vector_scale(float a, t_vector *v);
int         cylinder(t_data *data, int i, int j);
int         cone(t_data *data, int i, int j);
int         sphere(t_data *data, int i, int j);

# endif
