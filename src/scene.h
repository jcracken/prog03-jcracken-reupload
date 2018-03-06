#ifndef SCENE_H
#define SCENE_H

#include "pixel.h"
#include "color.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>

class scene {
  private:
    int width;
    int height;
    float eye[3];
    float lookat[3];
    float up[3];
    float angle;
    //surf vector
    pixel* data;
  public:
    scene();
    unsigned char* returnData();
    int returnWidth();
    int returnHeight();
    float* returnEye();
    float* returnLookAt();
    float* returnUp();
    float returnAngle();
    void acquireData(std::string name);
}
