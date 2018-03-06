#include "color.h"

color::color(){
  this->arr = [0 0 0];
}

color::color(const color &obj){
  this->arr = *obj.arr;
}

unsigned char* color::getColor(){
  return this->arr;
}

void color::setColor(unsigned char* color){
  this->arr[0] = color[0];
  this->arr[1] = color[1];
  this->arr[2] = color[2];
}
