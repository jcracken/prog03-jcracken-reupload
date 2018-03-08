#include "pixel.h"

pixel::pixel(){
  this->pixColor = color();
}

float* pixel::getColor(){
  return this->pixColor.getColor();
}

void pixel::setColor(float* color){
  this->pixColor.setColor(color);
}
