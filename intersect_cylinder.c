
#include "rt.h"
float ft_abs(float t)
{
    if(t < 0)
        return(-t);
    return(t);
}

int intersect_ray_cylinder(t_data *data, t_ray *ray, int current_cylinder, float *t)
{

    if(!data->cylinder)    
      return(0);
    data->a = dot_product_xz(&ray->dir, &ray->dir);
    data->dist = vector_sub_xz(&ray->start, &data->cylinder[current_cylinder].pos);
    data->b = 2 * dot_product_xz(&ray->dir, &data->dist);
    data->c = dot_product_xz(&data->dist, &data->dist) - data->cylinder[current_cylinder].radius * data->cylinder[current_cylinder].radius;
    data->discr = data->b * data->b - 4 * data->a * data->c;
    if (data->discr  <= 0)
    {
    return (0);
    }      
    else 
    {
        data->t0 =((-data->b + sqrt(data->discr)) / 2 * data->a);
        data->t1 = ((-data->b - sqrt(data->discr)) / 2 * data->a);
        if (data->t0 > data->t1)
            data->t0 = data->t1;
        if(data->t0 > 0 && data->t0 < *t)
        {
            *t = data->t0;
            return (1);
        }
    }
    
    return (0);
}