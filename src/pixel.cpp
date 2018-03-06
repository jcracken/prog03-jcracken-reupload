#include "pixel.h"

pixel::pixel(){
  this->pixColor = new color();
}

unsigned char* pixel::getColor(){
  return this->pixColor->getColor();
}

void pixel::setColor(unsigned char* color){
  this->pixColor->setColor(color);
}
