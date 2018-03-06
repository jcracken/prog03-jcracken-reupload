#ifndef COLOR_H
#define COLOR_H

class color {
  private:
    unsigned char arr[3];
  public:
    color();
    color( const color &obj );
    unsigned char* getColor();
    void setColor(unsigned char* color);
};
#endif
