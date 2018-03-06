#include "plane.h"

float* plane::getNormal(){
  return this->normal;
}

void plane::setNormal(float* normal){
  this->normal[0] = normal[0];
  this->normal[1] = normal[1];
  this->normal[2] = normal[2];
}
