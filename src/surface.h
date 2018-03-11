#ifndef SURFACE_H
#define SURFACE_H

#include "color.h"
#include "ray.h"

class surface { //all is public because setting parts private caused problems with child classes
  public:
    color ambient;
    color diffuse;
    color specular;
    float phong;
    float pos[3];
    bool type; //sphere or not
    surface();
    color getAmbient();
    color getDiffuse();
    color getSpecular();
    float getPhong();
    float* getPos();
    void setAmbient(float* ambient);
    void setDiffuse(float* diffuse);
    void setSpecular(float* specular);
    void setPhong(float phong);
    void setPos(float* pos);
    bool isSphere();
    bool detectCollision(ray* inter);
    void setNormal(float* norm); //these ones are the same thing--only exist cuz otherwise cpp throws a fit
    void setType();
    void setRadius(float rad);
    float* getNormal();
    float getRadius();
};
#endif
