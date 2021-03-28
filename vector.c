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

t_vector  cross_product(t_vector v1, t_vector v2)
{
 t_vector res;
 res.x = v1.y * v2.z - v1.z * v2.y;
 res.y = v1.z * v2.x - v1.x * v2.z;
 res.z = v1.x * v2.y - v1.y * v2.x;
 return(res);
}
