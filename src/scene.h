#ifndef SCENE_H
#define SCENE_H

#include "pixel.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>

class scene {
  private:
    int width;
    int height;
    int eye[3];
    int lookat[3];
    int up[3];
    float angle;
    //sphere vector
    //plane vector
    pixel* data;
  public:
    scene();
    unsigned char* returnData();
    int returnWidth();
    int returnHeight();
    int* returnEye();
    int* returnLookAt();
    int* returnUp();
    void acquireData(std::string name);
}
