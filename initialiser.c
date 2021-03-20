#include "rt.h"

void  fill_data(t_shape *shape, char **split, int i)
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
  if(ft_strcmp(split[0], "plane") == 0)
  {
    //if(ft_strcmp(split[9], "color") == 0)
    {
      shape->r = ft_atoi(split[11]);
      shape->g = ft_atoi(split[13]);
      shape->b = ft_atoi(split[15]); 
      shape->plane_rot[i] = ft_atoi(split[17]);
      //printf("color is %d\n", shape->color);
    }
  }
  if(ft_strcmp(split[0], "sphere") == 0)
     shape->sphere_rot[i] = ft_atoi(split[8]);
  if(ft_strcmp(split[0], "cylinder") == 0)
     shape->cylinder_rot[i] = ft_atoi(split[8]);
  
  shape->pos.x = ft_atoi(split[2])+ WIDTH/2;;
  shape->pos.y = ft_atoi(split[3])+ HEIGHT/2;
  shape->pos.z = ft_atoi(split[4]);
}

int data_init(t_data *data)
{


  char **split;

  data->sphere_count = 0;
  data->cylinder_count = 0;
  data->light_count = 0;
  data->plane_count = 0;
  data->cone_count = 0;
  data->sphere_check = 0;
  data->cylinder_check = 0;
  data->cone_check = 0;
  data->light_check = 0;
  data->plane_check = 0;
  data->cone_num = 0;
  data->sphere_num = 0;
  data->cylinder_num = 0;
  data->cylinder = NULL;
  data->sphere = NULL;
  data->cone = NULL;
  while (get_next_line(data->fd, &data->str) == 1)
  {
    if (!(split = ft_strsplit(data->str, ' ')))
    {
      ft_putstr("split error");
      return(0);
    }
    if (ft_strcmp(split[0], "sphere") == 0)
    {
      if (!data->sphere_check)
      {
        data->sphere_check = 1;
        data->sphere_num = ft_atoi(split[1]);
        data->sphere = (t_shape *)malloc(sizeof(t_shape) * data->sphere_num);
      }
      else
      {
        fill_data(&data->sphere[data->sphere_count], split, data->sphere_count);
        data->sphere[data->sphere_count].pos = rot(data->sphere[data->sphere_count].pos, data->sphere[data->sphere_count].sphere_rot[data->sphere_count]);

        data->sphere_count++;
      }
    }   
    else if (ft_strcmp(split[0], "cone") == 0)
    {
      if (!data->cone_check)
      {
        data->cone_check = 1;
        data->cone_num = ft_atoi(split[1]);
        data->cone = (t_shape *)malloc(sizeof(t_shape) * data->cone_num);
      }
      else
      {
        fill_data(&data->cone[data->cone_count], split, data->cone_count);
        data->cone_count++;
      }
    }
    else if (ft_strcmp(split[0], "cylinder") == 0)
    {
      if (!data->cylinder_check)
      {
        data->cylinder_check = 1;
        data->cylinder_num = ft_atoi(split[1]);
        data->cylinder = (t_shape *)malloc(sizeof(t_shape) * data->cylinder_num);
      }
      else
      {
        fill_data(&data->cylinder[data->cylinder_count], split, data->cylinder_count);
        data->cylinder[data->cylinder_count].pos = rot(data->cylinder[data->cylinder_count].pos, data->cylinder[data->cylinder_count].cylinder_rot[data->cylinder_count]);

        data->cylinder_count++;
      }
    }
    else if (ft_strcmp(split[0], "plane") == 0)
    {
      if (!data->plane_check)
      {
        data->plane_check = 1;
        data->plane_num = ft_atoi(split[1]);
        data->plane = (t_shape *)malloc(sizeof(t_shape) * data->plane_num);
      }
      else
      {
        fill_data(&data->plane[data->plane_count], split, data->plane_count);
        data->plane[data->plane_count].normal = rot(data->plane[data->plane_count].normal, data->plane[data->plane_count].plane_rot[data->plane_count]);

        data->plane_count++;
      }
    }
    else if (ft_strcmp(split[0], "light") == 0)
    {
      if (!data->light_check)
      {
        data->light_check = 1;
        data->light_num = ft_atoi(split[1]);
        data->light = (t_shape *)malloc(sizeof(t_shape) * data->light_num);
      }
      else
      {
        fill_data(&data->light[data->light_count], split, data->light_count);
        data->light_count++;
      }
    }
  }
  data->y = 0;
  data->r.dir.x = 0;
  data->r.dir.y = 0;
  data->r.dir.z = 1;
  //data->r.dir = rot(data->r.dir, 90);
  data->r.start.z = -10000;
  data->blue = 0;
  data->green = 0;
  data->red = 0;
}
