#include "rt.h"

float dot_product_xz(t_vector *v1, t_vector *v2)
{
    return( v1->x * v2->x + v1->z * v2->z );
}

t_vector vector_scale_xs(float a, t_vector *v)
{
    t_vector res;
    res.x = (v->x) * (a);
    res.z = (v->z) * (a);
    return (res);
}

t_vector vector_sub_xz(t_vector *v1, t_vector *v2)
{
    t_vector res;

    res.x = v1->x - v2->x;
    res.z = v1->z - v2->z;
    return (res);
}

t_vector vector_add_xz(t_vector *v1, t_vector *v2)
{
    t_vector res;

    res.x = v1->x + v2->x;
    res.z = v1->z + v2->z;
    return (res);
}