#include "rt.h"

void    find_cylinders(t_data *data, t_ray *r, int current_obj, float *t)
{
    if( intersect_ray_cylinder(data, r, current_obj, t))
    {
      if (*t < data->visible)
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
void find_spheres(t_data *data, t_ray *r, int current_obj, float *t)
{
    if( intersect_ray_sphere(data, r, current_obj, t))
    {
      if (*t < data->visible)
      {
        data->i_sphere = current_obj;
        data->i_cylinder = -1;
        data->i_cone = -1;
        data->intersect = 1;
        data->i_plane = -1;
        data->visible = *t;
      }      
    }
}

void find_cones(t_data *data, t_ray *r, int current_obj, float *t)
{
    if(intersect_ray_cone(data, r, current_obj, t))//first cone here no intersect, but first sphere intersect then second cone intersect
    {
      if (*t < data->visible)
      {
        data->i_cone = current_obj;
        data->i_cylinder = -1;
        data->i_plane = -1;
        data->i_sphere = -1;
        data->intersect = 1;
        data->visible = *t;
      }
    }
}

void find_planes(t_data *data, t_ray *r, int current_obj, float *t)
{
  if( intersect_ray_plane(data, r, current_obj, t))
  {
    if (*t < data->visible)
    {
      data->i_plane = current_obj;
      data->i_cone = -1;
      data->i_cylinder = -1;
      data->i_sphere = -1;
      data->intersect = 1;
      data->visible = *t;
    }
  }
}