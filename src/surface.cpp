#include "surface.h"

surface::surface(){
  this->ambient = new color();
  this->diffuse = new color();
  this->specular = new color();
  this->phong = 0.0;
  this->pos = [0.0 0.0 0.0];
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

void surface::setAmbient(color ambient){
  this->ambient = ambient;
}

void surface::setDiffuse(color diffuse){
  this->diffuse = diffuse;
}

void surface::setSpecular(color specular){
  this->specular = specular;
}

void surface::setPhong(float phong){
  this->phong = phong;
}

void surface::setPos(float* pos){
  this->pos[0] = pos[0];
  this->pos[1] = pos[1];
  this->pos[2] = pos[2];
}
