#include "plane.h"

float* plane::getNormal(){ //get normal of plane
  return this->normal;
}

void plane::setNormal(float* normal){ //set normal
  this->normal[0] = normal[0];
  this->normal[1] = normal[1];
  this->normal[2] = normal[2];
}

bool plane::detectCollision(ray* inter){ //run this to see if a ray collides with it
  float temp[3];
  float t, denom;

  denom = inter->dotProduct(this->normal, inter->getDirection());
  if(denom > 0.0000001){
    temp[0] = this->pos[0] - inter->getOrigin()[0];
    temp[1] = this->pos[1] - inter->getOrigin()[1];
    temp[2] = this->pos[2] - inter->getOrigin()[2];
    t = inter->dotProduct(temp, this->normal) / denom;
    if(t >= 0 && t <= inter->getT()){
      inter->setT(t);
      return true;
    }
  }
  return false;
}
