#ifndef PIXEL_H
#define PIXEL_H

#include "color.h"

class pixel {
  private:
    color pixColor;
  public:
    pixel();
    unsigned char* getColor();
    void setColor(unsigned char* color);
};
#endif
