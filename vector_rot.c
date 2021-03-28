#include "rt.h"

t_vector normalize(t_vector v)
{
  float temp;
  temp = 1 / sqrt(dot_product(&v, &v));
  return(vector_scale(temp, &v));
}

t_vector rot_z(t_vector v, float a)
{
  float pi;
  float rad;
  pi = 22 / 7;
  rad = a * pi / 180;
  float x;
  x = v.x;
  v.x = (v.x * cosf(rad) - v.y * sin(rad));// + v.x;/// +WIDTH/2 ;
  v.y = (x * sinf(rad) + v.y * cos(rad));// + v.x; // + HEIGHT/2 ;
  v.z = v.z;
  return(v);
}

t_vector rot_y(t_vector v, float a)
{
  float pi;
  float rad;
  float x;
  
  pi = 22 / 7;
  rad = a * pi / 180;
  x = v.x;
  v.x = (v.z * sinf(rad) + v.x * cosf(rad));// + WIDTH/2 ;
  v.z = (v.z * cosf(rad) - x * sinf(rad));// + HEIGHT/2 ;
  v.y = v.y; 
  return(v);
}