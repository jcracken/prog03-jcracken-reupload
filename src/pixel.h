#ifndef PIXEL_H
#define PIXEL_H

#include "color.h"

class pixel {
  private:
    color pixColor;
  public:
    pixel();
    float* getColor();
    void setColor(float* color);
};
#endif
