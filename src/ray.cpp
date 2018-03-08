#include "ray.h"

ray::ray(){
  this->origin[0] = 0;
  this->origin[1] = 0;
  this->origin[2] = 0;
  this->direction[0] = 0;
  this->direction[1] = 0;
  this->direction[2] = 0;
  this->t = 0.0;
}

float* ray::getOrigin(){
  return this->origin;
}

float* ray::getDirection(){
  return this->direction;
}

void ray::setOrigin(float* origin){
  this->origin[0] = origin[0];
  this->origin[1] = origin[1];
  this->origin[2] = origin[2];
}

void ray::setDirection(float* direction){
  this->direction[0] = direction[0];
  this->direction[1] = direction[1];
  this->direction[2] = direction[2];
}

float ray::getT(){
  return this->t;
}

void ray::setT(float t){
  this->t = t;
}

float ray::dotProduct(float* r0, float* r1){
  return (r0[0]*r1[0] + r0[1]*r1[1] + r0[2]*r1[2]);
}
