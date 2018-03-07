#ifndef RAY_H
#define RAY_H

class ray {
  private:
    float origin[3];
    float direction[3];
    float t;
  public:
    ray();
    float* getOrigin();
    float* getDirection();
    void setOrigin(float* origin);
    void setDirection(float* direction);
    float getT();
    void setT(float t);
    float dotProduct(float* r0, float* r1);
};
#endif
