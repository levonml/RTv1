#ifndef RT_H
# define RT_H
#include <mlx.h>
#include <math.h>

#include <stdio.h>

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

int intersect_ray_sphere(t_ray *r, t_sphere *s, float *t);
t_vector vector_add(t_vector *v1, t_vector *v2);
t_vector vector_sub(t_vector *v1, t_vector *v2);
float dot_product(t_vector *v1, t_vector *v2);
t_vector vector_scale(float a, t_vector *v);

# endif
