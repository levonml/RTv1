#include "rt.h"

void cylinder( t_data data)
{

  while(data.y < 800)
  {
      data.r.start.y = data.y;
      data.x = 0;
      while(data.x < 1080)
	    {
        data.t = -data.r.start.z;
        data.r.start.x = data.x;
        if (intersect_ray_cylinder(&data.r, &data.c, &data.t) == 1)
        {        
          data.blue = BLUE;
          data.green = GREEN ;
          data.red =  RED ;
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