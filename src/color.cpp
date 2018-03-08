#include "color.h"

color::color(){
  this->arr[0] = 0;
  this->arr[1] = 0;
  this->arr[2] = 0;
}

color::color(const color &obj){
  this->arr[0] = obj.arr[0];
  this->arr[1] = obj.arr[1];
  this->arr[2] = obj.arr[2];
}

float* color::getColor(){
  return this->arr;
}

void color::setColor(float* color){
  this->arr[0] = color[0];
  this->arr[1] = color[1];
  this->arr[2] = color[2];
}
