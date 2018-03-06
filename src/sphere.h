#ifndef SPHERE_H
#define SPHERE_H

#include "surface.h"

class sphere: public surface {
  private:
    float radius;
  public:
    void setRadius(float radius);
    float getRadius();
    void setType();
}
