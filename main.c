#include "rt.h"

int main(void)
{
  void	*mlx;
  void	*win;
  void	*image;
  char	*buffer;
  int	pixel_bits;
  int   line_bytes;
  int   endian;
  int x;
  int y;
  int color;
  int pixel;
  float t;
  t_ray light_ray;
  t_ray r;
  t_sphere s;
  t_light light;

 
  mlx = mlx_init();
  win = mlx_new_window(mlx, 1080, 800, "RT");
  image = mlx_new_image(mlx, 1080, 800);
  buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
  y = 0;
  light.pos.x = -800;
  light.pos.y = 400;
  light.pos.z = -4000;
  s.radius = 300;
  s.pos.x = 540;
  s.pos.y = 400;
  s.pos.z = 1;
  r.dir.x = 0;
  r.dir.y = 0;
  r.dir.z = 1;
  r.start.z = -1300;
  while(y < 800)
  {
      r.start.y = y;
      x = 0;
      while(x < 1080)
	    {
        t = -r.start.z;
        r.start.x = x;
        if (intersect_ray_sphere(&r, &s, &t) == 1)
        {
          t_vector scaled = vector_scale(t, &r.dir);
          t_vector new_start = vector_add(&r.start, &scaled);
          t_vector n = vector_sub(&new_start, &s.pos);
          float temp = dot_product(&n, &n);
          if(temp == 0)
            break ;
          temp = 1 / sqrt(temp);
          n = vector_scale(temp, &n);
          t_vector dist = vector_sub(&light.pos, &new_start);
          color = 0;
          if( dot_product(&dist, &n) >= 0)// continue;
          {
            float tt = sqrt(dot_product(&dist, &dist));
            //if (tt >= 0)// continue;
            {
              light_ray.start = new_start;
              light_ray.dir = vector_scale(1/tt, &dist); 
              float lambert = dot_product(&light_ray.dir, &n);
              color = 80;
              color *= lambert*lambert;
            }
          }
          

        }
          
	      else
	        color = 0;
	      pixel = y * line_bytes + x * 4;
	      buffer[pixel + 0] = color;
	      buffer[pixel + 1] = 0;
	      buffer[pixel + 2] = color;
	      buffer[pixel + 3] = 0;
	      x++;
	    }
      y++;
    }
  mlx_put_image_to_window(mlx, win, image, 0, 0);
  mlx_loop(mlx);
  return(0);
}
