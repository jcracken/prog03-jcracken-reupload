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

bool sphere::solveQuadratic(float a, float b, float c, float* t0, float* t1){
  float discr = b * b -4.0 * a * c;
  if (discr < 0.0) return false;
  else if (discr == 0) *t0 = *t1 = -0.5 * b / a;
  else {
    float q = (b > 0) ? -0.5 * (b + sqrt(discr)) : -0.5 * (b - sqrt(discr));
    *t0 = q / a;
    *t1 = c / q;
  }
  if (*t0 > *t1) std::swap(*t0, *t1);

  return true;
}

bool sphere::detectCollision(ray* inter){
  float temp[3];
  float t0, t1;

  temp[0] = inter->getOrigin()[0] - this->pos[0];
  temp[1] = inter->getOrigin()[1] - this->pos[1];
  temp[2] = inter->getOrigin()[2] - this->pos[2];
  float a = inter->dotProduct(inter->getDirection(), inter->getDirection()); //dir.dotProduct(dir)
  float b = 2 * inter->dotProduct(inter->getDirection(), temp); //dir.dotProduct(L)
  float c = inter->dotProduct(temp, temp) - powf(radius, 2.0); //L.dotProduct(L)
  if(!this->solveQuadratic(a, b, c, &t0, &t1)) return false;

  if(t0 > t1) std::swap(t0, t1);

  if (t0 < 0){
    t0 = t1;
    if(t0 < 0) return false;
  }
  if(t0 <= inter->getT()){
    inter->setT(t0);
    return true;
  }
  return false;
}
