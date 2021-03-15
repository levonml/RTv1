        
#include "rt.h"

int      cylinder(t_data *data, int current_cylinder, int i)
{
  int current_light;
  int d;

  data->scaled = vector_scale(data->t, &data->r.dir);
  data->new_start = vector_add(&data->r.start, &data->scaled);
  data->cylinder[current_cylinder].pos.y = data->new_start.y;
  data->n = vector_sub(&data->new_start, &data->cylinder[current_cylinder].pos);
  data->temp = dot_product(&data->n, &data->n);
  if(data->temp == 0)
    return(0);
  data->n = vector_scale(1 / sqrt(data->temp), &data->n);
  current_light = 0;
  while(current_light < data->light_num)
  {
    data->dist = vector_sub(&data->light[current_light].pos, &data->new_start);
    if( dot_product(&data->dist, &data->n) > 0 )
    {
      data->light_t = sqrt(dot_product(&data->dist, &data->dist));//!!!what is this for????!!!!
      if (data->light_t > 0)
      {
        data->light_ray.start = data->new_start;
        data->light_ray.dir = vector_scale(1 / data->light_t, &data->dist); 
        data->in_shadow = 0;
        d = 0;
        while (d < 7)
        {
          //if(!intersect_ray_cylinder(data, &data->light_ray, d, &data->light_t))
          if(find_intersection(data, &data->light_ray, d, &data->light_t))
          {
            //ft_putstr("lalalalalalalalalal");
            //printf("found intersectin\n");
            data->in_shadow = 1;
            break ;
          }
          d++;
        }
        if (data->in_shadow == 0)
        {
          //printf("data->t = %f", data->t);
          data->lambert = dot_product(&data->light_ray.dir, &data->n);
          data->blue = 0 ;
          data->green += GREEN * data->lambert;
          if (data->green > 255)
            data->green = 255;
          data->red =  0 ;
        }
      }
    }
    current_light++;
  }
  return(1);
}