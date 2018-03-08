#ifndef SURFACE_H
#define SURFACE_H

#include "color.h"
#include "ray.h"

class surface {
  public:
    color ambient;
    color diffuse;
    color specular;
    float phong;
    float pos[3];
    bool type;
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
};
#endif
