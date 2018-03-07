#include "sphere.h"

void sphere::setRadius(float radius){
  this->radius = radius;
}

float sphere::getRadius(){
  return radius;
}

void sphere::setType(){
  this->type = true;
}

bool solveQuadratic(float a, float b, float c, float* t0, float* t1){
  float discr = b * b -4.0 * a * c;
  if (discr < 0.0) return false;
  else if (discr == 0) t0 = t1 = -0.5 * b / a;
  else {
    float q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
    t0 = q / a;
    t1 = c / q;
  }
  if (t0 > t1) std::swap(t0, t1);

  return true;
}

bool detectCollision(ray inter){
  float temp[3];
  float origin[3] = inter.getOrigin();
  float direction[3] = inter.getDirection();
  float t0, t1;

  temp[0] = origin[0] - radius[0];
  temp[1] = origin[1] - radius[1];
  temp[2] = origin[2] - radius[2];
  float a = inter.dotProduct(direction, direction); //dir.dotProduct(dir)
  float b = 2 * inter.dotProduct(direction, temp); //dir.dotProduct(L)
  float c = inter.dotProduct(temp, temp) - powf(radius, 2.0); //L.dotProduct(L)
  if(!this->solveQuadratic(a, b, c, &t0, &t1)) return false;

  if(t0 > t1) std::swap(t0, t1);

  if (t0 < 0){
    t0 = t1;
    if(t0 < 0) return false;
  }

  inter.setT(t0);

  return true;
}
