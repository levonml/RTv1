
#include "rt.h"

float dot_product_c(t_vector *v1, t_vector *v2)
{
    return( v1->x * v2->x /*+ v1->y *v2->y*/ + v1->z * v2->z );
}

t_vector vector_scale_c(float a, t_vector *v)
{
    t_vector res;
    res.x = (v->x) * (a);
    //res.y = (v->y) * (a);
    res.z = (v->z) * (a);
    return (res);
}

t_vector vector_sub_c(t_vector *v1, t_vector *v2)
{
    t_vector res;

    res.x = v1->x - v2->x;
    //res.y = v1->y - v2->y;
    res.z = v1->z - v2->z;
    return (res);
}

t_vector vector_add_c(t_vector *v1, t_vector *v2)
{
    t_vector res;

    res.x = v1->x + v2->x;
    //res.y = v1->y + v2->y;
    res.z = v1->z + v2->z;
    return (res);
}

int intersect_ray_cylinder(t_data *data, int i)
{

    float discr;
    float a;
    float b;
    float c;
    float t0;
    float t1;
    t_vector dist;
    if(!data->cylinder)    
      return(0);
    a = dot_product_c(&data->r.dir, &data->r.dir);
    dist = vector_sub_c(&data->r.start, &data->cylinder[i].pos);
    b = 2 * dot_product_c(&data->r.dir, &dist);
    c = dot_product_c(&dist, &dist) - data->cylinder[i].radius * data->cylinder[i].radius;
    discr = b * b - 4 * a * c;
    if (discr  <=  0)
    {
       // ft_putstr("disco");
    return (0);
    }
        
    else 
    {
        t0 = (-b + sqrt(discr)) / 2 * a;
        t1 = (-b - sqrt(discr)) / 2 * a;
        if (t0 > t1)
            t0 = t1;
        if(t0 > 0 && t0 < data->t)
        {
            //data->cylinder_t = t0;
            data->t = t0;
            //printf("cilindric = %f", data->t);
            // printf("t = %f", *t);
            return (1);
        }
        else
            return (0);
    }
    
    //return (1);
}