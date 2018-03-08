#include "scene.h"

scene::scene(){
  this->width = 0;
  this->height = 0;
  this->eye[0] = 0.0;
  this->eye[1] = 0.0;
  this->eye[2] = 0.0;
  this->lookat[0] = 0.0;
  this->lookat[1] = 0.0;
  this->lookat[2] = 0.0;
  this->up[0] = 0.0;
  this->up[1] = 0.0;
  this->up[2] = 0.0;
  this->angle = 0.0;
  this->pixelLocCalc = false;
}

float** scene::returnData(){
  int i, j, a = 0, b = 0;
  float** returnData;
  returnData = new float*[this->height];
  for (i = 0; i < height; i++)
    returnData[i] = new float[3 * this->width];
  float* temp;
  for(i = 0; i < this->height; i++){
    for(j = 0; j < this->width; j++){
      temp = (this->data[i][j]).getColor();
      returnData[a][b] = temp[0];
      returnData[a][b + 1] = temp[1];
      returnData[a][b + 2] = temp[3];
      a++;
      b = b + 3;
    }
  }
  return returnData;
}

int scene::returnWidth(){
  return this->width;
}

int scene::returnHeight(){
  return this->height;
}

float* scene::returnEye(){
  return this->eye;
}

float* scene::returnLookAt(){
  return this->lookat;
}

float* scene::returnUp(){
  return this->up;
}

float scene::returnAngle(){
  return this->angle;
}

void scene::acquireData(std::string name){
  std::ifstream input(name, std::ifstream::in);
  std::string parse;
  bool follow = false;
  char type = '\0';

  light lTemp = light();
  sphere spTemp = sphere();
  plane pTemp = plane();

  float temp[3];
  int line = 0;
  //verifies file existence
  if(!(input.is_open())){
    std::cout << "File not found; try excluding the filename extension" << std::endl;
    exit(EXIT_FAILURE);
  }
  while(!input.eof()){
    getline(input, parse);
    if(parse.at(0) >= 65 && parse.at(0) <= 122){
      type = parse.at(0);
      follow = false;
    } else follow  = true;
    std::istringstream iss(parse);
    switch(type){
      case 'e':
        iss >> eye[0];
        iss >> eye[1];
        iss >> eye[2];
      break;
      case 'l':
        iss >> lookat[0];
        iss >> lookat[1];
        iss >> lookat[2];
      break;
      case 'u':
        iss >> up[0];
        iss >> up[1];
        iss >> up[2];
      break;
      case 'f':
        iss >> angle;
      break;
      case 'i':
        iss >> width;
        iss >> height;
      break;
      case 'L':
        iss >> temp[0];
        iss >> temp[1];
        iss >> temp[2];
        if(!follow){
          lTemp.setLoc(temp);
        } else {
          lTemp.setCol(temp);
          lights.push_back(lTemp);
        }
      break;
      case 'P':
        iss >> temp[0];
        if(line != 4) {
          iss >> temp[1];
          iss >> temp[2];
        }
        if(!follow){
          pTemp.setPos(temp);
          iss >> temp[0];
          iss >> temp[1];
          iss >> temp[2];
          pTemp.setNormal(temp);
          line = 1;
        } else {
          if(line == 1){
            pTemp.setAmbient(temp);
            line = 2;
          } else if (line == 2){
            pTemp.setDiffuse(temp);
            line = 3;
          } else if (line == 3){
            pTemp.setSpecular(temp);
            line = 4;
          } else {
            pTemp.setPhong(temp[0]);
            line = 0;
            surf.push_back(pTemp);
          }
        }
      break;
      case 'S':
        iss >> temp[0];
        if(line != 4) {
          iss >> temp[1];
          iss >> temp[2];
        }
        if(!follow){
          spTemp.setPos(temp);
          iss >> temp[0];
          spTemp.setRadius(temp[0]);
          line = 1;
        } else {
          if(line == 1){
            spTemp.setAmbient(temp);
            line = 2;
          } else if (line == 2){
            spTemp.setDiffuse(temp);
            line = 3;
          } else if (line == 3){
            spTemp.setSpecular(temp);
            line = 4;
          } else {
            spTemp.setPhong(temp[0]);
            line = 0;
            spTemp.setType();
            surf.push_back(spTemp);
          }
        }
      break;
      case 's':
        iss >> this->samples;
      break;
      default:
        std::cout << "input file malformed" << std::endl;
        exit(EXIT_FAILURE);
      break;
    }
    input.close();
  }
}

void scene::createPixelLoc(float* w, float* u, float* v){
  int i, j;
  float u, v, r, t, l, b, dist = powf((powf(this->eye[0] - this->lookat[0], 2)) + (powf(this->eye[1] - this->lookat[1], 2)) + (powf(this->eye[2] - this->lookat[2], 2)), 0.5);
  this->pixelLoc = new float*[this->height];
  for(i = 0; i < this->height; i++){
    this->pixelLoc[i] = new float[this->width];
  }
  for(i = 0; i < this->height; i++){
    for(j = 0; j < this->height; j++){
      u = i;
      v = j;
    }
  }
}

void scene::makeData(){
  this->data = new pixel*[this->height];
  int i, j, k, loc;
  float temp[3];
  float w[3] = {0};
  float u[3] = {0};
  float v[3] = {0};
  /*if(this->up[0] > 0.0){
    w[3] = {0, 0, -1};
    u[3] = {0, 1, 0};
  } else if (this->up[1] > 0.0){
    w[3] = {0, 0, -1};
    u[3] = {1, 0, 0};
  } else {
    w[3] = {0, -1, 0};
    u[3] = {1, 0, 0};
  }*/

  for(i = 0; i < this->height; i++){
    this->data[i] = new pixel[width];
  }

  if(!this->pixelLocCalc){
    createPixelLoc(w, u, v);
    this->pixelLocCalc = true;
  }

  for(i = 0; i < this->height; i++){
    for(j = 0; j < this->width; j++){
      //send ray for this pixel
      ray rTemp = ray();
      rTemp.setOrigin(this->eye);
      rTemp.setDirection(this->pixelLoc[i][j]);
      //calculate collision
      for(k = 0; (unsigned int)k < surf.size(); k++){
        if(surf.at(k).detectCollision(&rTemp)){
          loc = k;
        }
      }
      //calculate color
      //do stuff with surf at loc
    }
  }
}
