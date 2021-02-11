#ifndef RT_H
# define RT_H
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

#include <stdio.h>
#define RED 150
#define BLUE 0
#define GREEN 0

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

typedef struct  s_sphere
{
    t_vector    pos;
    float       radius;
}               t_sphere;

typedef struct s_data
{
    void	*mlx;
    void	*win;
    void	*image;
    char	*buffer;
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
    float   temp;
    t_sphere s;
    t_ray       r;
    t_ray       light_ray;
    t_light     light;
    t_vector    dist;
    t_vector scaled;
    t_vector new_start;
    t_vector n;
}               t_data;

int intersect_ray_sphere(t_ray *r, t_sphere *s, float *t);
t_vector vector_add(t_vector *v1, t_vector *v2);
t_vector vector_sub(t_vector *v1, t_vector *v2);
float dot_product(t_vector *v1, t_vector *v2);
t_vector vector_scale(float a, t_vector *v);

# endif
