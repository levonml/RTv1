#include "rt.h"

int sphere(t_data *data, int current_sphere, int current_light)
{
  int d;
  //printf("t= %f", data->t);
    data->scaled = vector_scale(data->t, &data->r.dir);
    data->new_start = vector_add(&data->r.start, &data->scaled);
    data->n = vector_sub(&data->new_start, &data->sphere[current_sphere].pos);
    data->temp = dot_product(&data->n, &data->n);
    if(data->temp == 0)
      return(0);
    data->temp = 1 / sqrt(data->temp);
    data->n = vector_scale(data->temp, &data->n);
    data->dist = vector_sub(&data->light[current_light].pos, &data->new_start);
    if( dot_product(&data->dist, &data->n) > 0 )
    {
      data->temp = sqrt(dot_product(&data->dist, &data->dist));
      if (data->temp > 0)
    
      data->light_ray.start = data->new_start;
      data->light_ray.dir = vector_scale(1 / data->temp, &data->dist); 
      //data->lambert = dot_product(&data->light_ray.dir, &data->n);
      data->in_shadow = 0;
      
      d = 0;
       while (d <  data->obj_num)
      {
        if(find_intersection(data, &data->light_ray, d))
        {
        //ft_putstr("found intersectin\n");
          data->in_shadow = 1;
          break ;
        }
        d++;
      }
      if (data->in_shadow == 0)
      {
        data->lambert = dot_product(&data->light_ray.dir, &data->n);
        data->blue = 0;
        data->green = 0;
        data->red +=  RED * data->lambert;
        if (data->red > 255)
          data->red = 255;
      }
       /*else 
      {
        data->blue = 0;
        data->green = 0;
        data->red = 0;
      }*/
    }
    return(1);
}