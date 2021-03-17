#include "rt.h"

int      plane(t_data *data, int current_plane, int i)
{
    int current_light;
    int d;
    //ft_putstr("ddddddddddddddddddd");
    //printf("data->t = %f", data->t);
    data->scaled = vector_scale(data->t, &data->r.dir);
    data->new_start = vector_add(&data->r.start, &data->scaled);
    //data->n = vector_sub(&data->new_start, &data->sphere[current_sphere].pos);
    data->temp = dot_product(&data->plane[current_plane].normal, &data->plane[current_plane].normal);
    if(data->temp == 0)
      return(0);
      //ft_putstr("ddddddddddddddddddd");
    data->temp = 1 / sqrt(data->temp);
    data->plane[current_plane].normal = vector_scale(data->temp, &data->plane[current_plane].normal);
    current_light = 0;
    while(current_light < data->light_num)
    {
      //ft_putstr("ddddddddddddddddddd");
      data->dist = vector_sub(&data->light[current_light].pos, &data->new_start);
      if( dot_product(&data->dist, &data->plane[current_plane].normal) != 0 )// or != 0???
      {
        //ft_putstr("ddddddddddddddddddd");
        data->light_t = sqrt(dot_product(&data->dist, &data->dist));
        if (data->light_t > 0)
        {
          data->light_ray.start = data->new_start;
          data->light_ray.dir = vector_scale(1 / data->light_t, &data->dist); 
          data->in_shadow = 0;
          d = 0;//max number of objects
          while (d < data->obj_num)
          {
            //printf("obj->num = %d", data->obj_num);
            //ft_putstr("ddddddddddddddddddd");
            //if( intersect_ray_cylinder(data, &data->light_ray, d, &data->light_t) )
            if(find_intersection(data, &data->light_ray, d, &data->light_t))
            //if( intersect_ray_sphere(data, &data->light_ray, d, &data->light_t) )
            {
              //ft_putstr("ddddddddddddddddddd");
              data->in_shadow = 1;
              break ;
            }           
            d++;
          }
          if (!data->in_shadow)
          {
            data->lambert = dot_product(&data->light_ray.dir, &data->plane[current_plane].normal);
            data->blue += data->plane[current_plane].b * data->lambert ;
            if (data->blue > 255)
              data->blue = 255;
            data->green += data->plane[current_plane].g * data->lambert;
            if (data->green > 255)
              data->green = 255;
            data->red +=  data->plane[current_plane].r *data->lambert;//(0.8 + 1 / data->t)
            if (data->red > 255)
              data->red = 255;
          }
        }
      }
      current_light++;
    }
    return(0);
}