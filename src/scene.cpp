#include "scene.h"

scene::scene(){
  this->width = 0;
  this->height = 0;
  this->eye = [0.0 0.0 0.0];
  this->lookat = [0.0 0.0 0.0];
  this->up = [0.0 0.0 0.0];
  this->angle = 0.0;
}

float* scene::returnData(){
  int i, j;
  float* returnData = new float[height][3 * width];
  flaot* temp[3];
  for(i = 0; i < this->height; i++){
    for(j = 0; j < this->width; j = j + 3){
      temp = this->data[i][j]->getColor();
      returnData[i][j] = temp[0];
      returnData[i][j + 1] = temp[1];
      returnData[i][j + 2] = temp[3];
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

  light lTemp = new light();
  sphere spTemp = new sphere();
  plane pTemp = new plane();

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
    istringstream iss(parse);
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
        iss >> width
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
          }
          surf.push_back(pTemp);
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
          }
          surf.push_back(spTemp);
        }
      break;
    }
  }
}

void scene::makeData(){
  this->data = new pixel[this->height][this->width];
  int i, j;

  for(i = 0; i < this->height; i++){
    for(j = 0; j < this->width; j++){
      //send ray for this pixel

      //calculate collision

      //calculate color

    }
  }
}
