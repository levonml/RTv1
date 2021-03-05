#include "rt.h"

void  fill_data(t_shape *shape, char **split)
{
  shape->radius = ft_atoi(split[6]);
  shape->pos.x = ft_atoi(split[2]);
  shape->pos.y = ft_atoi(split[3]);
  shape->pos.z = ft_atoi(split[4]);
}

int data_init(t_data *data)
{

  char **split;
  int sphere_count;
  int cylinder_count;
  int cone_count;
  int num;
  int sphere_check;
  int cylinder_check;
  int cone_check;

  sphere_count = 0;
  cylinder_count = 0;
  cone_count = 0;
  sphere_check = 0;
  cylinder_check = 0;
  cone_check = 0;
  while (get_next_line(data->fd, &data->str) == 1)
  {
    if (!(split = ft_strsplit(data->str, ' ')))
    {
      ft_putstr("split error");
      return(0);
    }
    //printf("split[1] = %s", split[0]);
    if (ft_strcmp(split[0], "sphere") == 0)
    {
      //ft_putstr("ffffffffff\n");
      if (!sphere_check)
      {
        sphere_check = 1;
        num = ft_atoi(split[1]);
 
        printf("num = %d", num);
        data->sphere = (t_shape *)malloc(sizeof(t_shape) * num);
      }
      else
      {
        fill_data(&data->sphere[sphere_count], split);
        sphere_count++;
        //ft_putstr("ffffffffff\n");
      }
    }
  
    else if (ft_strcmp(split[0], "cone") == 0)
    {
      //ft_putstr("ffffffffff\n");
      if (!cone_check)
      {
        //ft_putstr("conefffff\n");
        cone_check = 1;
        num = ft_atoi(split[1]);
        data->cone = (t_shape *)malloc(sizeof(t_shape) * num);
      }
      else
      {
        fill_data(&data->cone[cone_count], split);
        cone_count++;
      }
    }
     else if (ft_strcmp(split[0], "cylinder") == 0)
    {
      if (!cylinder_check)
      {
        cylinder_check = 1;
        num = ft_atoi(split[1]);
        data->cylinder = (t_shape *)malloc(sizeof(t_shape) * num);
      }
      else
      {
        fill_data(&data->cylinder[cylinder_count], split);
        cylinder_count++;
        //ft_putstr("ffffffffff\n");
      }
      //ft_putstr("ffffffffff\n");
    }
  }
  
/*data->cylinder = (t_shape *)malloc(sizeof(t_shape) * 4);
data->sphere = (t_shape *)malloc(sizeof(t_shape) * 4);
data->cone = (t_shape *)malloc(sizeof(t_shape) * 4);*/
  data->y = 0;
  data->light.pos.x = 1800;
  data->light.pos.y = 400;
  data->light.pos.z = -2000;
 /* data->sphere[1].radius = 200;
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
  data->cylinder[0].radius = 150;
  data->cylinder[0].pos.x = 840;
  data->cylinder[0].pos.y = 400;
  data->cylinder[0].pos.z = 0;
  data->cone[0].radius = 110;
  data->cone[0].pos.x = 900;
  data->cone[0].pos.y = 10;
  data->cone[0].pos.z = 0;*/
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
          if( intersect_ray_cylinder(&data, iter) )
            i = iter;
          iter++;
        }
       // printf("i = %d", data.x);
        if (i != -1) 
          {
          //  if (!sphere(&data, i))
            //  break ;
            if (!cylinder(&data, i))
              break ;
           // if (!cone(&data, i))
             // break ;
          }
            else 
        {
          data.blue = 0;
          data.green = 0;
          data.red = 0;
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

int main(int argc, char **argv)
{
  t_data    *data;

  if(!(data = malloc(sizeof(t_data))))
    return(0);
  if(argc != 2)
  {
    ft_putstr("one argument must be given");
    return(0);
  }
  if(!(data->fd = open(argv[1], O_RDONLY)) && data->fd == -1)
  {
    ft_putstr("file opening error");
    return(0);
  }
  data_init(data);
  data->mlx = mlx_init();
  data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "RT");
  data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
  data->buffer = mlx_get_data_addr(data->image, &data->pixel_bits, &data->line_bytes, &data->endian);
  mlx_key_hook(data->win, key_control, data);
  mlx_expose_hook(data->win, expose_hook, data);
  mlx_loop(data->mlx);
  return(0);
}
