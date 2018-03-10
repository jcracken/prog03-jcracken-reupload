#include "surface.h"

surface::surface(){ //constructor
  this->ambient = color();
  this->diffuse = color();
  this->specular = color();
  this->phong = 0.0;
  this->pos[0] = 0.0;
  this->pos[1] = 0.0;
  this->pos[2] = 0.0;
  this->type = false;
}

color surface::getAmbient(){ //returns ambient color value
  return this->ambient;
}

color surface::getDiffuse(){ //returns diffuse color value
  return this->diffuse;
}

color surface::getSpecular(){ //returns specular color value
  return this->specular;
}

float surface::getPhong(){ //returns phong exponent value
  return this->phong;
}

float* surface::getPos(){ //point where the surface is based (sphere center/plane loc)
  return this->pos;
}

void surface::setAmbient(float* ambient){ //update ambient color
  this->ambient.setColor(ambient);
}

void surface::setDiffuse(float* diffuse){ //update diffuse color
  this->diffuse.setColor(diffuse);
}

void surface::setSpecular(float* specular){ //update specular color
  this->specular.setColor(specular);
}

void surface::setPhong(float phong){ //update phong exponent
  this->phong = phong;
}

void surface::setPos(float* pos){ //update position
  this->pos[0] = pos[0];
  this->pos[1] = pos[1];
  this->pos[2] = pos[2];
}

bool surface::isSphere(){ //returns true if it's a sphere
  return this->type;
}

bool surface::detectCollision(ray* inter){ //here because i can't call it for children otherwise apparently
  //potatoes
  return true;
}

void surface::setNormal(float* norm){ //see inside comment and above
  //why have polymorphism if it just makes things more complicated
}

void surface::setType(){ //set if it's a sphere or a plane
  this->type = true;
}

void surface::setRadius(float rad){ //see above
  //sigh
}

float* surface::getNormal(){ //see above
  //i hate everything
  float temp = 0.0;
  return &temp;
}

float surface::getRadius(){ //see above
  float radius = 0.0;
  return radius;
}
