#include "rt.h"

void  fill_data(t_shape *shape, char **split)
{
  shape->radius = ft_atoi(split[6]);
  shape->pos.x = WIDTH/2 + ft_atoi(split[2]);
  shape->pos.y = ft_atoi(split[3]) + HEIGHT/2;
  //shape->pos.x = ft_atoi(split[2]);
  //shape->pos.y = ft_atoi(split[3]);
  shape->pos.z = ft_atoi(split[4]);
}

int data_init(t_data *data)
{

  char **split;
  int sphere_count;
  int cylinder_count;
  int num;
  int sphere_check;
  int cylinder_check;
  int cone_check;

  sphere_count = 0;
  cylinder_count = 0;
  data->cone_count = 0;
  sphere_check = 0;
  cylinder_check = 0;
  cone_check = 0;
  data->cylinder = NULL;
  data->sphere = NULL;
  data->cone = NULL;
  while (get_next_line(data->fd, &data->str) == 1)
  {
    printf("%s\n",data->str);
    if (!(split = ft_strsplit(data->str, ' ')))
    {
      ft_putstr("split error");
      return(0);
    }
    if (ft_strcmp(split[0], "sphere") == 0)
    {
      if (!sphere_check)
      {
        sphere_check = 1;
        num = ft_atoi(split[1]);
        data->sphere = (t_shape *)malloc(sizeof(t_shape) * num);
      }
      else
      {
        fill_data(&data->sphere[sphere_count], split);
        sphere_count++;
      }
    }
    else if (ft_strcmp(split[0], "cone") == 0)
    {
      if (!cone_check)
      {
        cone_check = 1;
        data->cone_num = ft_atoi(split[1]);
        data->cone = (t_shape *)malloc(sizeof(t_shape) * data->cone_num);
      }
      else
      {
        fill_data(&data->cone[data->cone_count], split);
        data->cone_count++;
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
      }
    }
  }
  data->y = 0;
  data->light.pos.x = WIDTH/2 - 300;
  data->light.pos.y = 0;
  data->light.pos.z = -1000;
  data->r.dir.x = 0;
  data->r.dir.y = 0;
  data->r.dir.z = 1;
  data->r.start.z = -15000;
  data->red = 0;
  data->green = 0;
  data->blue = 0;
}
void render(t_data *data)
{
  int iter;
  int i_cylinder;
  int i_sphere;
  int i_cone;

  while(data->y < HEIGHT)
  {
      data->r.start.y = data->y;
      data->x = 0;
      while(data->x < WIDTH)
	    {
        data->t = 50000;
        data->r.start.x = data->x;
        iter = 0;
        i_cylinder = -1;
        i_sphere = -1;
        i_cone = -1;
        while(iter < 8)
        {
          if( intersect_ray_cylinder(data, iter) )
            i_cylinder = iter;
          if(intersect_ray_cone(data, iter))
          {
            i_cone = iter;
            i_cylinder = -1;
          }

          if( intersect_ray_sphere(data, iter))
          {
            i_sphere = iter;
            i_cone = -1;
            i_cylinder = -1;
          }
          iter++;
      }
        if (i_cylinder != -1) 
        {
          if (!cylinder(data, i_cylinder))
            break ;
        }
        else if(i_sphere != -1)
        {
          if (!sphere(data, i_sphere))
            break ;
        }
        else if(i_cone != -1)
        {
          if (!cone(data, i_cone))
            break ;
        }
        else 
        {
          data->blue = 0;
          data->green = 0;
          data->red = 0;
        }   
	      data->pixel = data->y * data->line_bytes + data->x * 4;
	      data->buffer[data->pixel + 0] = data->blue;
	      data->buffer[data->pixel + 1] = data->green;
	      data->buffer[data->pixel + 2] = data->red;
	      data->buffer[data->pixel + 3] = 0;
        data->x++;
	    }
      data->y++;
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
  render(data);
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
