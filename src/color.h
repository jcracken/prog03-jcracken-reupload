#ifndef COLOR_H
#define COLOR_H

class color {
  private:
    float arr[3];
  public:
    color();
    color( const color &obj );
    float* getColor();
    void setColor(float* color);
};
#endif
