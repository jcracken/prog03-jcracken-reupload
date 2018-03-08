#ifndef PLANE_H
#define PLANE_H

#include "surface.h"

class plane: public surface {
  private:
    float normal[3];
  public:
    float* getNormal();
    void setNormal(float* normal);
    bool detectCollision(ray* inter);
};
#endif
