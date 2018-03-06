#include "scene.h"

scene::scene(){
  this->width = 0;
  this->height = 0;
  this->eye = [0.0 0.0 0.0];
  this->lookat = [0.0 0.0 0.0];
  this->up = [0.0 0.0 0.0];
  this->angle = 0.0;
}

unsigned char* scene::returnData(){
  int i, j;
  unsigned char* returnData = new unsigned char[height][width];
  for(i = 0; i < this->height; i++){
    for(j = 0; j < this->width; j++){
      returnData[i][j] = this->data[i][j]->getColor();
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
        //lights
      break;
      case 'S':
        //sphere
      break;
      case 'P':
        //plane
      break;
    }
  }
}
