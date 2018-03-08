#ifndef SCENE_H
#define SCENE_H

#include "pixel.h"
#include "color.h"
#include "light.h"
#include "sphere.h"
#include "plane.h"
#include "surface.h"
#include "ray.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <math.h>
#include <cmath>
#include <vector>
#include <algorithm>

class scene {
  private:
    int width;
    int height;
    float eye[3];
    float lookat[3];
    float up[3];
    float angle;
    int samples;
    pixel** data;
    std::vector<light> lights;
    std::vector<surface> surf;
    std::vector<ray> rays;
    float*** pixelLoc;
  public:
    scene();
    int returnWidth();
    int returnHeight();
    float* returnEye();
    float* returnLookAt();
    float* returnUp();
    float** returnData();
    float returnAngle();
    void acquireData(std::string name);
    void makeData();
    void createPixelLoc(float* w, float* u, float* v, float dist);
};
#endif
