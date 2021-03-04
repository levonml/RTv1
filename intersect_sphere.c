
#include "rt.h"

float dot_product(t_vector *v1, t_vector *v2)
{
    return( v1->x * v2->x + v1->y *v2->y + v1->z * v2->z );
}

t_vector vector_scale(float a, t_vector *v)
{
    t_vector res;
    res.x = (v->x) * (a);
    res.y = (v->y) * (a);
    res.z = (v->z) * (a);
    return (res);
}

t_vector vector_sub(t_vector *v1, t_vector *v2)
{
    t_vector res;

    res.x = v1->x - v2->x;
    res.y = v1->y - v2->y;
    res.z = v1->z - v2->z;
    return (res);
}

t_vector vector_add(t_vector *v1, t_vector *v2)
{
    t_vector res;

    res.x = v1->x + v2->x;
    res.y = v1->y + v2->y;
    res.z = v1->z + v2->z;
    return (res);
}

int intersect_ray_sphere(t_data *data, int i)
{

    float discr;
    float a;
    float b;
    float c;
    float t0;
    float t1;
    t_vector dist;

    a = dot_product(&data->r.dir, &data->r.dir);
    dist = vector_sub(&data->r.start, &data->sphere[i].pos);
    b = 2 * dot_product(&data->r.dir, &dist);
    c = dot_product(&dist, &dist) - data->sphere[i].radius * data->sphere[i].radius;
    discr = b * b - 4 * a * c;
    if (discr  < 0)
        return (0);
    else 
    {
        t0 = (-b + sqrt(discr)) / 2;
        t1 = (-b - sqrt(discr)) / 2;
    }
    if (t0 > t1)
        t0 = t1;
    if(t0 > 0 && t0 < data->t)
    {
        //data->sphere_t = t0;
        data->t = t0;
        return (1);
    }
    
    return (0);
}