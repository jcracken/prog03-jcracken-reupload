#include "light.h"

light::light(){
  this->loc[0] = 0.0;
  this->loc[1] = 0.0;
  this->loc[2] = 0.0;
  this->col = color();
}

void light::setLoc(float* loc){
  this->loc[0] = loc[0];
  this->loc[1] = loc[1];
  this->loc[2] = loc[2];
}

void light::setCol(float* col){
  this->col.setColor(col);
}

float light::getLoc(){
  return *this->loc;
}

color light::getCol(){
  return this->col;
}
