#include "ray.h"

ray::ray(){ //constructor
  this->origin[0] = 0;
  this->origin[1] = 0;
  this->origin[2] = 0;
  this->direction[0] = 0;
  this->direction[1] = 0;
  this->direction[2] = 0;
  this->t = 0.0;
}

float* ray::getOrigin(){ //return origin
  return this->origin;
}

float* ray::getDirection(){ //return direction
  return this->direction;
}

void ray::setOrigin(float* origin){ //set origin
  this->origin[0] = origin[0];
  this->origin[1] = origin[1];
  this->origin[2] = origin[2];
}

void ray::setDirection(float* direction){ //set direction
  this->direction[0] = direction[0];
  this->direction[1] = direction[1];
  this->direction[2] = direction[2];
}

float ray::getT(){ //return t where ray collided with surf
  return this->t;
}

void ray::setT(float t){ //set t where collision
  this->t = t;
}

float ray::dotProduct(float* r0, float* r1){ //was originally static function, w/e
  return (r0[0]*r1[0] + r0[1]*r1[1] + r0[2]*r1[2]);
}

float* ray::crossProduct(float* r0, float* r1){ //ditto
  float temp[3];

  temp[0] = r0[1] * r1[2] - r1[1] * r0[2];
  temp[1] = r1[0] * r0[2] - r0[0] * r1[2];
  temp[2] = r0[0] * r1[1] - r1[0] * r0[1];

  return temp;
}
