#ifndef PLANE_H
#define PLANE_H

#include "surface.h"

class plane: public surface { //child of surface
  private:
    float normal[3];
  public:
    float* getNormal();
    void setNormal(float* normal);
    bool detectCollision(ray* inter);
};
#endif
