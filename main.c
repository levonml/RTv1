#include "rt.h"

void data_init(t_data *data)
{
  int i;
  i =  0;

  //data->sphere = (t_sphere *)malloc(sizeof(data->sphere) * 3);

  data->y = 0;
  data->light.pos.x = 1000;
  data->light.pos.y = 400;
  data->light.pos.z = -4000;
  data->sphere[1].radius = 200;
  data->sphere[1].pos.x = 1000;
  data->sphere[1].pos.y = 600;
  data->sphere[1].pos.z = 100;
  data->sphere[0].radius = 200;
  data->sphere[0].pos.x = 1000;
  data->sphere[0].pos.y = 200;
  data->sphere[0].pos.z = 100;
  data->sphere[2].radius = 200;
  data->sphere[2].pos.x = 300;
  data->sphere[2].pos.y = 200;
  data->sphere[2].pos.z = 100;
  data->cylinder.radius = 150;
  data->cylinder.pos.x = 840;
  data->cylinder.pos.y = 400;
  data->cylinder.pos.z = 0;
  data->cone.radius = 110;
  data->cone.pos.x = 900;
  data->cone.pos.y = 10;
  data->cone.pos.z = 0;
  data->r.dir.x = 0;
  data->r.dir.y = 0;
  data->r.dir.z = 1;
  data->r.start.z = -13000;
  data->red = 0;
  data->green = 0;
  data->blue = 0;
}
void render(t_data data)
{
  int iter;
  int i;

  while(data.y < HEIGHT)
  {
      data.r.start.y = data.y;
      data.x = 0;
      while(data.x < WIDTH)
	    {
        data.t = -data.r.start.z;
        data.r.start.x = data.x;
        iter = 0;
        i = -1;
        while(iter < 3)
        {
          if(intersect_ray_sphere(&data, iter))
          {
            i = iter;
          }
          iter++;
        }
        if (i == -1) 
          break ;
        {
        if (!sphere(&data, i))
          break ;
        }
      /*  else 
        {
          data.blue = 0;
          data.green = 0;
          data.red = 0;
        }   */     
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
  if (key == 65307) 
    exit(0); 
  return (0);
}

int expose_hook(void *d)
{
  t_data *data;

  data = (t_data *)d;
  render(*data);
  mlx_put_image_to_window(data->mlx, data->win, data->image, 0, 0);
  return(0);
}

int main(void)
{
  t_data    data;
 
  data.mlx = mlx_init();
  data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "RT");
  data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT);
  data.buffer = mlx_get_data_addr(data.image, &data.pixel_bits, &data.line_bytes, &data.endian);
  data_init(&data);
  mlx_key_hook(data.win, key_control, &data);
  mlx_expose_hook(data.win, expose_hook, &data);
  mlx_loop(data.mlx);
  return(0);
}
