#include "ray.h"

ray::ray(){
  this->origin = [0 0 0];
  this->direction = [0 0 0];
}

int* ray::getOrigin(){
  return this->origin;
}

int* ray::getDirection(){
  return this->direction;
}

void ray::setOrigin(int* origin){
  this->origin[0] = origin[0];
  this->origin[1] = origin[1];
  this->origin[2] = origin[2];
}

void ray::setDirection(int* direction){
  this->direction[0] = direction[0];
  this->direction[1] = direction[1];
  this->direction[2] = direction[2];
}

boolean ray::detectCollision(int* goal){
  //if collision, return true. if not, return false.

  return false;
}
