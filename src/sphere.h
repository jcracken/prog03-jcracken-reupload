#ifndef SPHERE_H
#define SPHERE_H

#include "surface.h"
#include <math.h>
#include <utility>

class sphere: public surface { //child of surface
  private:
    float radius;
    bool solveQuadratic(float a, float b, float c, float* t0, float* t1);
  public:
    void setRadius(float radius);
    float getRadius();
    void setType();
    bool detectCollision(ray* inter);
};
#endif
