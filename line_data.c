#include "rt.h"
t_shape *allocate(t_shape *shape, int num)
{
  if(!(shape = (t_shape *)malloc(sizeof(t_shape) * num)))
    exit(0);
  return (shape);
}
void line_data_sphere(t_data *data)
{
      if (!data->sphere_check)
      {
        data->sphere_check = 1;
        data->sphere_num = ft_atoi(data->split[1]);
        data->sphere = allocate(data->sphere, data->sphere_num);
      }
      else
      {
        fill_data(data->sphere, data, data->sphere_count);
        data->sphere[data->sphere_count].pos = rot_z(data->sphere[data->sphere_count].pos,\
        data->sphere[data->sphere_count].sphere_rot[data->sphere_count]);

        data->sphere_count++;
      }
}

void line_data_cone(t_data *data)
{
      if (!data->cone_check)
      {
        data->cone_check = 1;
        data->cone_num = ft_atoi(data->split[1]);
        data->cone = allocate(data->cone, data->cone_num);
      }
      else
      {
        fill_data(data->cone, data, data->cone_count);
        data->cone_count++;
      }
}
void line_data_cylinder(t_data *data)
{
      if (!data->cylinder_check)
      {
        data->cylinder_check = 1;
        data->cylinder_num = ft_atoi(data->split[1]);
        data->cylinder = allocate(data->cylinder, data->cylinder_num);
      }
      else
      {
        fill_data(data->cylinder, data, data->cylinder_count);
        data->cylinder[data->cylinder_count].pos = rot_z(data->cylinder[data->cylinder_count].pos, data->cylinder[data->cylinder_count].cylinder_rot[data->cylinder_count]);

        data->cylinder_count++;
      }
}

void line_data_plane(t_data *data)
{
      if (!data->plane_check)
      {
        data->plane_check = 1;
        data->plane_num = ft_atoi(data->split[1]);
        data->plane = allocate(data->plane, data->plane_num);
      }
      else
      {
        fill_data(data->plane, data, data->plane_count);
        data->plane[data->plane_count].normal = rot_z(data->plane[data->plane_count].normal, data->plane[data->plane_count].plane_rot[data->plane_count]);

        data->plane_count++;
      }
}

void line_data_light(t_data *data)
{
      if (!data->light_check)
      {
        data->light_check = 1;
        data->light_num = ft_atoi(data->split[1]);
        data->light = allocate(data->light, data->light_num);;
      }
      else
      {
        fill_data(data->light, data, data->light_count);
        data->light_count++;
      }
}

void line_data_camera(t_data *data)
{

    data->camera = allocate(data->camera, 1);
    fill_data(data->camera, data, 0);

}