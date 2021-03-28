
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
    //data->cylinder[current_cylinder].pos.y = data->y;
    //data->cam.start.y = -200;//data->y;
    /*data->a = dot_product_xz(&ray->dir, &ray->dir);
    data->dist = vector_sub_xz(&ray->start, &data->cylinder[current_cylinder].pos);
    data->b = 2 * dot_product_xz(&ray->dir, &data->dist);
    data->c = dot_product_xz(&data->dist, &data->dist) - pow(data->cylinder[current_cylinder].radius, 2);*/
    t_vector o = data->cylinder[current_cylinder].pos;
    //printf("pos = %f\n,", data->cylinder[current_cylinder].pos.y);
    o.y = data->cam.start.y;
    t_vector horizontal = (vector_sub(&o, &data->cam.start));
    //printf("pos = %f\n", horizontal.y);
    t_vector horizontal_norm = normalize(horizontal);
    t_vector dir = ray->dir;
    dir.y = 0 ;
    //printf("dir = %f, hor = %f", dir.x, horizontal.x);
    float f = dot_product(&dir, &horizontal_norm);
    float alfa = acos(f);
    //printf("alfa = %f", alfa);
    float tc = sin(alfa) * sqrt(dot_product(&horizontal, &horizontal));
    if(tc > data->cylinder[current_cylinder].radius)
       return(0);
    float ti1 =  sqrt(pow(data->cylinder[current_cylinder].radius, 2)  - pow(tc, 2));
    float ti2 =  -sqrt(pow(data->cylinder[current_cylinder].radius, 2)  - pow(tc, 2));
    //float tp = tc / tan(alfa);
    float tp = f * sqrt(dot_product(&horizontal, &horizontal));
    float ip1 = tp - ti1;
    float ip2 = tp - ti2;
    t_vector d = ray->dir;
    d.z = 0;
    horizontal_norm.z = 0;
    float b = dot_product(&d, &horizontal_norm);
    float beta = acos(b);
    data->t0 = ip1 / cos(beta);
    data->t1 = ip2 / cos(beta);
    
    //printf("pos = %f\n,", data->t0);
    //t_vector scale1 = vector_scale(pp1, &ray->dir);
    //t_vector scale2 = vector_scale(pp2, &ray->dir);
    //data->t0 = vector_add(&data->cam.start, &scale1);
    //data->t1 = vector_add(&data->cam.start, &scale2);
        if (data->t0 > data->t1)
            data->t0 = data->t1;
        if(data->t0 > 0 && data->t0 < *t)
        {        
            *t = data->t0;
            //t_vector s = vector_scale(*t, &ray->dir);
            //t_vector intersect = vector_add(&data->cam.start, &s); 
            //printf("pos = %f\n,", intersect.y);
            return (1);
        }
    /*if (data->discr  <= 0)
        return (0);      
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
    }*/
    
    return (0);
}