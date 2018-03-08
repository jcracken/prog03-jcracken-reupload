#include "surface.h"

surface::surface(){
  this->ambient = color();
  this->diffuse = color();
  this->specular = color();
  this->phong = 0.0;
  this->pos[0] = 0.0;
  this->pos[1] = 0.0;
  this->pos[2] = 0.0;
  this->type = false;
}

color surface::getAmbient(){
  return this->ambient;
}

color surface::getDiffuse(){
  return this->diffuse;
}

color surface::getSpecular(){
  return this->specular;
}

float surface::getPhong(){
  return this->phong;
}

float* surface::getPos(){
  return this->pos;
}

void surface::setAmbient(float* ambient){
  this->ambient.setColor(ambient);
}

void surface::setDiffuse(float* diffuse){
  this->diffuse.setColor(diffuse);
}

void surface::setSpecular(float* specular){
  this->specular.setColor(specular);
}

void surface::setPhong(float phong){
  this->phong = phong;
}

void surface::setPos(float* pos){
  this->pos[0] = pos[0];
  this->pos[1] = pos[1];
  this->pos[2] = pos[2];
}

bool surface::isSphere(){
  return this->type;
}

bool surface::detectCollision(ray* inter){
  //potatoes
  return true;
}
