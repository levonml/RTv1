#include "rt.h"

static float dot_product_c(t_vector *v1, t_vector *v2)
{
    return( v1->x * v2->x /*+ v1->y *v2->y*/ + v1->z * v2->z );
}

static t_vector vector_scale_c(float a, t_vector *v)
{
    t_vector res;
    res.x = (v->x) * (a);
    //res.y = (v->y) * (a);
    res.z = (v->z) * (a);
    return (res);
}

static t_vector vector_sub_c(t_vector v1, t_vector v2)
{
    t_vector res;

    res.x = v1.x - v2.x;
    //res.y = v1->y - v2->y;
    res.z = v1.z - v2.z;
    return (res);
}

static t_vector vector_add_c(t_vector *v1, t_vector *v2)
{
    t_vector res;

    res.x = v1->x + v2->x;
    //res.y = v1->y + v2->y;
    res.z = v1->z + v2->z;
    return (res);
}


int intersect_ray_cone(t_data *data, t_ray *ray, int current)
{

    float discr;
    float a;
    float b;
    float c;
    float t0;
    float t1;
    t_vector dist;
    
    if(!data->cone || (data->cone_count - 1) < current)
      return(0);
    a = dot_product_c(&ray->dir, &ray->dir);
    dist = vector_sub_c(data->r.start, data->cone[current].pos);
    b = 2 * dot_product_c(&ray->dir, &dist);
    c = dot_product_c(&dist, &dist) - (data->y  - HEIGHT/2) * (data->y - HEIGHT/2)/6;
    discr = b * b - 4 * a * c;
    if (discr < 0)
        return (0);
    t0 = (-b + sqrt(discr)) / 2 * a;
    t1 = (-b - sqrt(discr)) / 2 * a;
    if (t0 > t1)
        t0 = t1;
    if(t0 > 0 && t0 < data->t)
    {
        data->t = t0;
        return (1);
    }
    else
        return (0);
return (0);
}