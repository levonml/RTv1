        
#include "rt.h"

int      cylinder(t_data *data, int current_cylinder, int current_light)
{

    data->scaled = vector_scale(data->t, &data->r.dir);
    data->new_start = vector_add(&data->r.start, &data->scaled);
    data->cylinder[current_cylinder].pos.y = data->new_start.y;
    data->n = vector_sub(&data->new_start, &data->cylinder[current_cylinder].pos);
    data->temp = dot_product(&data->n, &data->n);
    if(data->temp == 0)
      return(0);
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
        int d;
        d = 0;
       /* while (d < data->obj_num)
        {
          if( !intersect_ray_cylinder(data, &data->light_ray, d) )
         // if(find_intersection(data, &data->light_ray, d))
          {
            //printf("found intersectin\n");
            data->in_shadow = 1;
            data->blue = 50;
            data->green = 50;
            data->red = 50;
            break ;
          }
          d++;
        }*/
      if (data->in_shadow == 0)
      {
        data->lambert = dot_product(&data->light_ray.dir, &data->n);
        data->blue = 0 ;
        data->green += GREEN * data->lambert;
        if (data->green > 255)
          data->green = 255;
        data->red =  0 ;
      }
     /*  else 
      {
        data->blue = 0;
        data->green = 0;
        data->red = 0;
      }*/
    }
    return(1);
}