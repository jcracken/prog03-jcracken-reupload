#include "plane.h"

float* plane::getNormal(){
  return this->normal;
}

void plane::setNormal(float* normal){
  this->normal[0] = normal[0];
  this->normal[1] = normal[1];
  this->normal[2] = normal[2];
}

bool detectCollision(ray inter){
  float temp[3];
  float origin[3] = inter->getOrigin();
  float direction[3] = inter->getDirection();
  float point[3] = this->pos;
  float t, denom;

  denom = inter->dotProduct(this->normal, direction);
  if(denom > 0.0000001){
    temp[0] = pos[0] - origin[0];
    temp[1] = pos[1] - origin[1];
    temp[2] = pos[2] - origin[2];
    t = inter->dotProduct(temp, this->normal) / denom;
    if(t >= 0){
      inter->setT(t);
      return true;
    }
  }
  return false;
}
