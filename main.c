#include "rt.h"
int   max_num(int a, int b, int c, int d)
{
  if(a < b)
    a = b;
  if (a < c)
    a = c;
  if(a < d)
    a = d;
    return(a);
}
t_vector rot(t_vector v, float a)
{
  float pi;
  float rad;
  pi = 22 / 7;
  rad = a * pi / 180;
  float x;
  x = v.x;
  //printf("x = %f\ny = %f\nz = %f\n cosA = %f\nsinA = %f\nA = %d\n", v.x, v.y, v.z, cos(a), sin(a), a);
 //rotate over z
  //v.x = (v.x * cosf(rad) - v.y * sinf(rad)) + WIDTH/2 ;
  //v.y = (x * sinf(rad) + v.y * cosf(rad)) + HEIGHT/2 ;
  //over Y;
  v.x = (v.z * sinf(rad) + v.x * cosf(rad));// + WIDTH/2 ;
  v.z = (v.z * cosf(rad) - x * sinf(rad));// + HEIGHT/2 ;
  v.y = v.y;// + 400;
  //printf("rad = %f\nx = %f\ny = %f\nz = %f\n cosA = %f\nsinA = %f\n", rad, v.x, v.y, v.z, cosf(rad), sinf(rad));
  //printf("1 = %f\n2 = %f\n", v.x * cosf(rad), v.y * sinf(rad));
    //v.z = v.z;
  return(v);
}

int   find_intersection(t_data *data, t_ray *r, int current_obj, float *t)
{
  data->intersect = 0;
  data->visible = *t;

  if(current_obj < data->cylinder_num)
    find_cylinders(data, r, current_obj, t);
  if(current_obj < data->sphere_num)
    find_spheres(data, r, current_obj, t);
  if(current_obj < data->cone_num)
    find_cones(data, r, current_obj, t);
  if(current_obj < data->plane_num)
   find_planes(data, r, current_obj, t);
  return(data->intersect);
}
int   iterate_over_objects(t_data *data, int iter)
{
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
    if (!plane(data, data->i_plane, data->iter_light))
       return(0);  
  }
  return(1);
}
void iter_over_x(t_data *data)
{
    data->t = 50000;
    data->r.start.x = data->x;
    data->iter = 0;
    data->i_cylinder = -1;
    data->i_sphere = -1;
    data->i_cone = -1;
    data->i_plane = -1;
    data->red = 0;
    data->green = 0;
    data->blue = 0;
    while(data->iter < data->obj_num)
    {
      find_intersection(data, &data->r, data->iter, &data->t);
      data->iter++;
    }
    iterate_over_objects(data, data->iter_light);
	  data->pixel = data->y * data->line_bytes + data->x * 4;
	  data->buffer[data->pixel + 0] = data->blue;
	  data->buffer[data->pixel + 1] = data->green;
	  data->buffer[data->pixel + 2] = data->red;
	  data->buffer[data->pixel + 3] = 0;
}

void render(t_data *data)
{
  data->obj_num = max_num(data->cone_num, data->cylinder_num, data->sphere_num, data->plane_num);
  if (data->sphere[1].pos.z)
    data->sphere[1].radius = data->sphere[1].radius - (data->sphere[1].pos.z / data->sphere[1].radius * 4);
  while(data->y < HEIGHT)
{
  data->r.start.y = data->y;
  data->x = 0;
  while(data->x < WIDTH)
	{
    iter_over_x(data);
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
    ft_putstr("The number of arguments should be one");
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
