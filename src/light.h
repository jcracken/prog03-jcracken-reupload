#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"

class light {
  private:
    float loc[3];
    color col;
  public:
    light();
    void setLoc(float* loc);
    void setCol(color col);
    float getLoc();
    color getCol();
}
