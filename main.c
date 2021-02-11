#include "rt.h"

void data_init(t_data *data)
{
  data->y = 0;
  data->light.pos.x = 0;
  data->light.pos.y = 400;
  data->light.pos.z = -1000;
  data->s.radius = 300;
  data->s.pos.x = 540;
  data->s.pos.y = 400;
  data->s.pos.z = 1;
  data->r.dir.x = 0;
  data->r.dir.y = 0;
  data->r.dir.z = 1;
  data->r.start.z = -1300;
  data->red = 0;
  data->green = 0;
  data->blue = 0;
}
void sphere( t_data data)
{
  while(data.y < 800)
  {
      data.r.start.y = data.y;
      data.x = 0;
      while(data.x < 1080)
	    {
        data.t = -data.r.start.z;
        data.r.start.x = data.x;
        if (intersect_ray_sphere(&data.r, &data.s, &data.t) == 1)
        {
          data.scaled = vector_scale(data.t, &data.r.dir);
          data.new_start = vector_add(&data.r.start, &data.scaled);
          data.n = vector_sub(&data.new_start, &data.s.pos);
          data.temp = dot_product(&data.n, &data.n);
          if(data.temp == 0)
            break ;
          data.temp = 1 / sqrt(data.temp);
          data.n = vector_scale(data.temp, &data.n);
          data.dist = vector_sub(&data.light.pos, &data.new_start);

          if( dot_product(&data.dist, &data.n) >= 0 )
          {
            data.temp = sqrt(dot_product(&data.dist, &data.dist));
            if (data.temp == 0)
              break ;
              data.light_ray.start = data.new_start;
              data.light_ray.dir = vector_scale(1 / data.temp, &data.dist); 
              float lambert = dot_product(&data.light_ray.dir, &data.n);
              data.blue = BLUE * lambert;
              data.green = GREEN * lambert;
              data.red =  RED * lambert;
              //if( vector_add()
          }
        }
	      else
        {
	        data.red = 0;
          data.green = 0;
          data.blue = 0;
        }
	      data.pixel = data.y * data.line_bytes + data.x * 4;
	      data.buffer[data.pixel + 0] = data.blue;
	      data.buffer[data.pixel + 1] = data.green;
	      data.buffer[data.pixel + 2] = data.red;
	      data.buffer[data.pixel + 3] = 0;
	      data.x++;
	    }
      data.y++;
    }
}
int key_control(int key, void *d)
{
  t_data *data;
 
  data = (t_data *)d;
  if( key == 50)
  {
    data->s.pos.x = 1100;
  }
  if (key == 65307) 
    exit(0);
    printf("x = %f\n", data->s.pos.x);  
    printf("x = %d\n", key);  
 
  
 //if(key == 49)
    sphere(*data);
    mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
  return (0);
}

int expose_hook(void *d)
{
  t_data *data;

  data = (t_data *)d;
  mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
  return(0);
}

int main(void)
{
  t_data    data;
 
  data.mlx = mlx_init();
  data.win = mlx_new_window(data.mlx, 1080, 800, "RT");
  data.image = mlx_new_image(data.mlx, 1080, 800);
  data.buffer = mlx_get_data_addr(data.image, &data.pixel_bits, &data.line_bytes, &data.endian);
  data_init(&data);
  sphere(data);
  mlx_key_hook(data.win, key_control, &data);
  mlx_expose_hook(data.win, expose_hook, &data);
  mlx_loop(data.mlx);
  return(0);
}
