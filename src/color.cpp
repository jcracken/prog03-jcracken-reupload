#include "color.h"

color::color(){ //constructor
  this->arr[0] = 0.0;
  this->arr[1] = 0.0;
  this->arr[2] = 0.0;
}

color::color(const color &obj){ //copy constructor -- originally used in code, don't believe this is the case anymore
  this->arr[0] = obj.arr[0];
  this->arr[1] = obj.arr[1];
  this->arr[2] = obj.arr[2];
}

float* color::getColor(){ //return color values as float array
  return this->arr;
}

void color::setColor(float* color){ //set color using float array
  this->arr[0] = color[0];
  this->arr[1] = color[1];
  this->arr[2] = color[2];
}
