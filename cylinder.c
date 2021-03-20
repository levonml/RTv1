        
#include "rt.h"

static void choose_color(t_data *data)
{
  data->lambert = dot_product(&data->light_ray.dir, &data->n);
  data->blue = 0 ;
  data->green += GREEN * data->lambert;
  if (data->green > 255)
    data->green = 255;
  data->red =  0 ;
}
static void get_new_ray(t_data *data)
{
  data->light_ray.start = data->new_start;
  data->light_ray.dir = vector_scale(1 / data->light_t, &data->dist); 
  data->in_shadow = 0;
  data->count = 0;
  while (data->count > data->obj_num)
  {
    if(find_intersection(data, &data->light_ray, data->count, &data->light_t))
    {
      data->in_shadow = 1;
      break ;
    }
    data->count++;
  }
  if (data->in_shadow == 0)
    choose_color(data); 
}
int      cylinder(t_data *data, int current_cylinder, int i)
{

  data->scaled = vector_scale(data->t, &data->r.dir);
  data->new_start = vector_add(&data->r.start, &data->scaled);
  data->cylinder[current_cylinder].pos.y = data->new_start.y;
  data->n = vector_sub(&data->new_start, &data->cylinder[current_cylinder].pos);
  data->temp = dot_product(&data->n, &data->n);
  if(data->temp == 0)
    return(0);
  data->n = vector_scale(1 / sqrt(data->temp), &data->n);
  data->current_light = 0;
  while(data->current_light < data->light_num)
  {
    data->dist = vector_sub(&data->light[data->current_light].pos, &data->new_start);
    if( dot_product(&data->dist, &data->n) > 0 )
    {
      data->light_t = sqrt(dot_product(&data->dist, &data->dist));//!!!what is this for????!!!!
      if (data->light_t > 0)
        get_new_ray(data);
    }
    data->current_light++;
  }
  return(1);
}