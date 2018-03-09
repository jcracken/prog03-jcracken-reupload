#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"

class light {
  private:
    float loc[3];
    color col;
    float a[3];
    float b[3];
  public:
    light();
    void setLoc(float* loc);
    void setCol(float* col);
    void setA(float* a);
    void setB(float* b);
    float* getLoc();
    color getCol();
    float* getA();
    float* getB();
};
#endif
