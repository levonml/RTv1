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
#include <unistd.h>
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
    t_vector    normal;
    float       radius;
    float     sphere_rot[10];
    float     cylinder_rot[10];
    float     plane_rot[10];
    int         r;
    int         b;
    int         g;
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
    int     obj_num;
    int     iter_light;
    int     i_cylinder;
    int     i_sphere;
    int     i_cone;
    int     i_plane;
    int     iter;
    int     intersect;
    int     in_shadow;
    int     x;
    int     y;
    float   red;
    float   green;
    float   blue;
    int     pixel;
    float   visible;
    float   t;
    float   light_t;
    float   sphere_t;
    float   cylinder_t;
    float   cone_t;
    float   temp;
    float   lambert;
    float   discr;
    float   a;
    float   b;
    float   c;
    float   t0;
    float   t1;
    int     count;
    int     num;
    int     current_light;
    int     sphere_value;
    int     cylinder_value;
    int     sphere_count;
    int     cylinder_count;
    int     light_count;
    int     cone_count;
    int     plane_count;
    int     cone_num;
    int     sphere_num;
    int     plane_num;
    int     cylinder_num;
    int     light_num;
    int     sphere_check;
    int     cylinder_check;
    int     cone_check;
    int     light_check;
    int     plane_check;
    t_shape *sphere;
    t_shape *cylinder;
    t_shape *cone;
    t_shape *plane;
    t_shape *light;
    t_ray       r;
    t_ray       light_ray;
   // t_light     light;
    t_vector    dist;
    t_vector scaled;
    t_vector new_start;
    t_vector n;
}               t_data;

int         intersect_ray_sphere(t_data *data, t_ray *ray, int i, float *t);
int         intersect_ray_cylinder(t_data *data, t_ray *ray, int i, float *t);
int         intersect_ray_cone(t_data *data, t_ray *ray, int i, float *t);
int         intersect_ray_plane(t_data *data, t_ray *ray, int i, float *t);
t_vector    vector_add(t_vector *v1, t_vector *v2);
t_vector    vector_sub(t_vector *v1, t_vector *v2);
t_vector    vector_scale(float a, t_vector *v);
t_vector    vector_sub_xz(t_vector *v1, t_vector *v2);
t_vector    vector_add_xz(t_vector *v1, t_vector *v2);
t_vector    vector_scale_xz(float a, t_vector *v);
t_vector    rot(t_vector v, float a);
float       dot_product(t_vector *v1, t_vector *v2);
float       dot_product_xz(t_vector *v1, t_vector *v2);
float       ft_abs(float t);

int         data_init(t_data *data);
int         cylinder(t_data *data, int i, int j);
int         cone(t_data *data, int i, int j);
int         sphere(t_data *data, int i, int j);
int         plane(t_data *data, int i, int j);
int         find_intersection(t_data *data, t_ray *ray, int i, float *t);
void    find_cylinders(t_data *data, t_ray *r, int current_obj, float *t);
void    find_cones(t_data *data, t_ray *r, int current_obj, float *t);
void    find_spheres(t_data *data, t_ray *r, int current_obj, float *t);
void    find_planes(t_data *data, t_ray *r, int current_obj, float *t);

# endif
