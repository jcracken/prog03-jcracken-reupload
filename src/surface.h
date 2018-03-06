#ifndef SURFACE_H
#define SURFACE_H

#include "color.h"

class surface {
  private:
    color ambient;
    color diffuse;
    color specular;
    float phong;
    float pos[3];
  public:
    surface();
    color getAmbient();
    color getDiffuse();
    color getSpecular();
    float getPhong();
    float* getPos();
    void setAmbient(color ambient);
    void setDiffuse(color diffuse);
    void setSpecular(color specular);
    void setPhong(float phong);
    void setPos(float* pos);
}