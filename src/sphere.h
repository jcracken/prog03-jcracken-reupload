#ifndef SPHERE_H
#define SPHERE_H

#include "surface.h"

class sphere: public surface {
  private:
    float radius;
    bool solveQuadratic(float a, float b, float c, float* t0, float* t1);
  public:
    void setRadius(float radius);
    float getRadius();
    void setType();
};
#endif
