#include "rt.h"

int cone(t_data *data, int i)
{       
    data->scaled = vector_scale(data->t, &data->r.dir);
    data->new_start = vector_add(&data->r.start, &data->scaled);
    data->cone[i].pos.y = data->new_start.y;
    data->n = vector_sub(&data->new_start, &data->cone[i].pos);
    data->temp = dot_product(&data->n, &data->n);
    if(data->temp == 0)
      return(0);
    //data->temp = 1 / sqrt(data->temp);
    data->n = vector_scale(1 / sqrt(data->temp), &data->n);
    data->dist = vector_sub(&data->light.pos, &data->new_start);
    if( dot_product(&data->dist, &data->n) >= 0 )
    {
      data->temp = sqrt(dot_product(&data->dist, &data->dist));
      if (data->temp == 0)
       return(0);
      data->light_ray.start = data->new_start;
      data->light_ray.dir = vector_scale(1 / data->temp, &data->dist); 
      data->lambert = dot_product(&data->light_ray.dir, &data->n);
      data->blue = BLUE * data->lambert;
      data->green = 0;
      data->red =  0;
    }
return (1);
}