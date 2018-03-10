#include "light.h"

light::light(){
  this->loc[0] = 0.0;
  this->loc[1] = 0.0;
  this->loc[2] = 0.0;
  this->col = color();
  this->a[0] = 0.0;
  this->a[1] = 0.0;
  this->a[2] = 0.0;
  this->b[0] = 0.0;
  this->b[1] = 0.0;
  this->b[2] = 0.0;
}

void light::setLoc(float* loc){
  this->loc[0] = loc[0];
  this->loc[1] = loc[1];
  this->loc[2] = loc[2];
}

void light::setCol(float* col){
  this->col.setColor(col);
}

float* light::getLoc(){
  return this->loc;
}

color light::getCol(){
  return this->col;
}

void light::setA(float* a){
  this->a[0] = a[0];
  this->a[1] = a[1];
  this->a[2] = a[2];
}

void light::setB(float* b){
  this->b[0] = b[0];
  this->b[1] = b[1];
  this->b[2] = b[2];
}

float* light::getA(){
  return this->a;
}

float* light::getB(){
  return this->b;
}
