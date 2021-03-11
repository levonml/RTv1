#include "rt.h"

int cone(t_data *data, int current_cone, int current_light)
{    
  int d;   
  //printf("radius = %f", data->cone->radius);
    data->scaled = vector_scale(data->t, &data->r.dir);
    data->new_start = vector_add(&data->r.start, &data->scaled);
    data->cone[current_cone].pos.y = data->new_start.y;
    data->n = vector_sub(&data->new_start, &data->cone[current_cone].pos);
    //data->n = data->new_start;
    data->temp = dot_product(&data->n, &data->n);
    if(data->temp <= 0)
      return(0);
    //data->temp = 1 / sqrt(data->temp);
    data->n = vector_scale(1 / sqrt(data->temp), &data->n);
    data->dist = vector_sub(&data->light[current_light].pos, &data->new_start);
    if( dot_product(&data->dist, &data->n) >= 0 )
    {
      data->temp = sqrt(dot_product(&data->dist, &data->dist));
      if (data->temp <= 0)
       return(0);
      data->light_ray.start = data->new_start;
      data->light_ray.dir = vector_scale(1 / data->temp, &data->dist); 
      data->in_shadow = 0;
      
      d = 0;
      while (d < 3)
      {
         if( intersect_ray_sphere(data, &data->light_ray, d) )
        //if(find_intersection(data, &data->light_ray, d))
        {
          data->in_shadow = 1;
          break ;
        }
        d++;
      }
      if (!data->in_shadow)
      {
        data->lambert = dot_product(&data->light_ray.dir, &data->n);
        data->blue += BLUE * data->lambert;
        if (data->blue > 255)
          data->blue = 255;
        data->green = 0;
        data->red =  0;
      }
      /* else 
      {
        data->blue = 0;
        data->green = 0;
        data->red = 0;
      }*/
    }
return (1);
}