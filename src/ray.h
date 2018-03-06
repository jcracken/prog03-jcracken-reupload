#ifndef RAY_H
#define RAY_H

class ray {
  private:
    int origin[3];
    int direction[3];
  public:
    ray();
    int* getOrigin();
    int* getDirection();
    void setOrigin(int* origin);
    void setDirection(int* direction);
    boolean detectCollision(int* goal);
};
#endif
