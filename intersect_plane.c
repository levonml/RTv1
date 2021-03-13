#include "rt.h"

int intersect_ray_plane(t_data *data, t_ray *ray, int current_plane, float *t)
{
    float a;
    float b;
    float t1;
    t_vector plane;

    if(!data->plane)
      return(0);
    plane = vector_sub(&data->plane[current_plane].pos, &data->r.start);
    a = dot_product(&data->plane[current_plane].normal, &plane);
    b = dot_product(&data->plane[current_plane].normal, &data->r.dir);
    if (b == 0)
        return(0);
    t1 = a / b;
    if (t1 < 0 && t1 >= *t)
        return(0);
    return (1);
}