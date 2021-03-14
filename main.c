#include "rt.h"
int   max_num(int a, int b, int c)
{
  if(a < b)
    a = b;
  if (a < c)
    a = c;
    return(a);
}
void  fill_data(t_shape *shape, char **split)
{
  if(ft_strcmp(split[5], "normal") == 0)
  {
    shape->normal.x = ft_atoi(split[6]);
    shape->normal.y = ft_atoi(split[7]);
    shape->normal.z = ft_atoi(split[8]);
  } 
  else if(ft_strcmp(split[5], "radius") == 0)
  {
    shape->radius = ft_atoi(split[6]);
  }
  shape->pos.x = WIDTH/2 + ft_atoi(split[2]);
  shape->pos.y = ft_atoi(split[3]) + HEIGHT/2;
  shape->pos.z = ft_atoi(split[4]);
}
int   find_intersection(t_data *data, t_ray *r, int current_obj, float *t)
{
  data->intersect = 0;
  data->visible = *t;

    //if(current_obj < data->cylinder_num)
  {
    if( intersect_ray_cylinder(data, r, current_obj, t))
    {
      //if (*t < data->visible)
      {
        data->i_cylinder = current_obj;
        data->i_sphere = -1;
        data->i_cone = -1;
        data->i_plane = -1;
        data->intersect = 1;
         data->visible = *t;
      }
    }
  }
    //if(current_obj < data->sphere_num)
  {
    if( intersect_ray_sphere(data, r, current_obj, t))
    {
     // if (*t < data->visible)
      {
        data->i_sphere = current_obj;
        data->i_cylinder = -1;
        data->i_cone = -1;
        data->intersect = 1;
        data->i_plane = -1;
      }      
    }
  }
    //if(current_obj < data->cone_num)
  {
    if(intersect_ray_cone(data, r, current_obj, t))//first cone here no intersect, but first sphere intersect then second cone intersect
    {
     // if (*t < data->visible)
      {
        data->i_cone = current_obj;
        data->i_cylinder = -1;
        data->i_plane = -1;
        data->i_sphere = -1;
        data->intersect = 1;
      }
    }
  }
  //if(current_obj < data->plane_num)
  {
    if( intersect_ray_plane(data, r, current_obj, t))
    {
      //ft_putstr("llllllllllllllllllllll");
      data->i_plane = current_obj;
      data->i_cone = -1;
      data->i_cylinder = -1;
      data->i_sphere = -1;
      data->intersect = 1;
    }
  }
  return(data->intersect);
}
int   iterate_over_objects(t_data *data, int iter)
{
  //ft_putstr("here!!!!!!!!!!!1\n");
  //printf("dddddd= ");
  if (data->i_cylinder != -1) 
  {
    if (!cylinder(data, data->i_cylinder, data->iter_light))
      return(0);
  }
  else if(data->i_sphere != -1)
  {
    if (!sphere(data, data->i_sphere, data->iter_light))
      return(0);
  }
  else if(data->i_cone != -1)
  {
    if (!cone(data, data->i_cone, data->iter_light))
      return(0);
  }
  else if(data->i_plane != -1)
  {
    //ft_putstr("ddddddddddddddddddd");
    if (!plane(data, data->i_plane, data->iter_light))
      return(0);
  }
 /* else 
  {
    data->blue = 0;
    data->green = 0;
    data->red = 0;
  }*/
  return(1);
}

int data_init(t_data *data)
{

  char **split;
  int sphere_count;
  int cylinder_count;
  int light_count;
  int plane_count;
  int cone_count;
  int num;
  int sphere_check;
  int cylinder_check;
  int cone_check;
  int light_check;
  int plane_check;

  sphere_count = 0;
  cylinder_count = 0;
  light_count = 0;
  plane_count = 0;
  cone_count = 0;
  sphere_check = 0;
  cylinder_check = 0;
  cone_check = 0;
  light_check = 0;
  plane_check = 0;
  data->cone_num = 0;
  data->sphere_num = 0;
  data->cylinder_num = 0;
  data->cylinder = NULL;
  data->sphere = NULL;
  data->cone = NULL;
  while (get_next_line(data->fd, &data->str) == 1)
  {
    //printf("%s\n",data->str);
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
        data->sphere_num = ft_atoi(split[1]);
        data->sphere = (t_shape *)malloc(sizeof(t_shape) * data->sphere_num);
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
        data->cylinder_num = ft_atoi(split[1]);
        data->cylinder = (t_shape *)malloc(sizeof(t_shape) * data->cylinder_num);
      }
      else
      {
        fill_data(&data->cylinder[cylinder_count], split);
        cylinder_count++;
      }
    }
    else if (ft_strcmp(split[0], "plane") == 0)
    {
      if (!plane_check)
      {
        plane_check = 1;
        data->plane_num = ft_atoi(split[1]);
        data->plane = (t_shape *)malloc(sizeof(t_shape) * data->plane_num);
      }
      else
      {
        fill_data(&data->plane[plane_count], split);
        plane_count++;
      }
    }
    else if (ft_strcmp(split[0], "light") == 0)
    {
      if (!light_check)
      {
        light_check = 1;
        data->light_num = ft_atoi(split[1]);
        data->light = (t_shape *)malloc(sizeof(t_shape) * data->light_num);
      }
      else
      {
        fill_data(&data->light[light_count], split);
        light_count++;
      }
    }
  }
  data->y = 0;
  data->r.dir.x = 0;
  data->r.dir.y = 0;
  data->r.dir.z = 1;
  data->r.start.z = -1000;
  data->blue = 0;
  data->green = 0;
  data->red = 0;
}
void render(t_data *data)
{
  int light_num;

  data->obj_num = max_num(data->cone_num, data->cylinder_num, data->sphere_num);
  while(data->y < HEIGHT)
{
  data->r.start.y = data->y;
  data->x = 0;
  while(data->x < WIDTH)
	{
    data->blue = 0;
    data->green = 0;
    data->red = 0;
    data->t = 50000;
    data->r.start.x = data->x;
    data->iter = 0;
    data->i_cylinder = -1;
    data->i_sphere = -1;
    data->i_cone = -1;
    int e;
    e = 0;
    while (e < 1)
    {
      //data->t = 50000;
      data->red = 0;
      data->green = 0;
      data->blue = 0;
      while(data->iter < data->obj_num)
      {
        find_intersection(data, &data->r, data->iter, &data->t);
        data->iter++;
      }
      //data->iter_light = 0;
      iterate_over_objects(data, data->iter_light);
      /*while(data->iter_light < 1)//data->light_num)
      {
        if(!iterate_over_objects(data, data->iter_light))
          break ;
       // data->iter_light++;
      }*/
	    data->pixel = data->y * data->line_bytes + data->x * 4;
	    data->buffer[data->pixel + 0] = data->blue;
	    data->buffer[data->pixel + 1] = data->green;
	    data->buffer[data->pixel + 2] = data->red;
	    data->buffer[data->pixel + 3] = 0;
      e++;
    }
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
  close(data->fd);
  data->mlx = mlx_init();
  data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "RT");
  data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
  data->buffer = mlx_get_data_addr(data->image, &data->pixel_bits, &data->line_bytes, &data->endian);
  mlx_key_hook(data->win, key_control, data);
  mlx_expose_hook(data->win, expose_hook, data);
  mlx_loop(data->mlx);
  return(0);
}
