#include "light.h"

light::light(){
  this->loc = [0.0 0.0 0.0];
  this->col = new color();
}

void light::setLoc(float* loc){
  this->loc = loc;
}

void light::setCol(color col){
  this->col = col;
}

float light::getLoc(){
  return this->loc;
}

color light::getCol(){
  return this->col;
}
