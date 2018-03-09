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
  int line = 0, lineA = 0;
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
      case 'A':
        iss >> temp[0];
        iss >> temp[1];
        iss >> temp[2];
        if(!follow){
          lTemp.setLoc(temp);
          iss >> temp[0];
          iss >> temp[1];
          iss >> temp[2];
          lTemp.setA(temp);
          iss >> temp[0];
          iss >> temp[1];
          iss >> temp[2];
          lTemp.setB(temp);
        } else {
          lTemp.setCol(temp);
          lights.push_back(lTemp);
        }
      break;
      default:
        std::cout << "input file malformed" << std::endl;
        exit(EXIT_FAILURE);
      break;
    }
    input.close();
  }
}

void scene::createPixelLoc(float* w, float* u, float* v, float dist){
  int i, j;
  float uVar, vVar, r, t, l, b;
  ray thisShouldBeStatic = ray(); //needed because my compilier throws a fit whenever i try to use static functions
  this->pixelLoc = new float**[this->height];
  for(i = 0; i < this->height; i++){
    this->pixelLoc[i] = new float*[this->width];
  }

  float imageHeight = std::tan(this->angle / 2.0) * dist;
  float imageWidth = std::tan((this->angle * this->width / this->height) / 2.0) * dist;
  r = thisShouldBeStatic.dotProduct(this->lookat, u) + imageWidth / 2.0;
  l = thisShouldBeStatic.dotProduct(this->lookat, u) - imageWidth / 2.0;
  t = thisShouldBeStatic.dotProduct(this->lookat, v) + imageHeight / 2.0;
  b = thisShouldBeStatic.dotProduct(this->lookat, v) - imageHeight / 2.0;

  for(i = 0; i < this->height; i++){
    for(j = 0; j < this->height; j++){
      uVar = l + (r - l) * (i + 0.5) / (this->width);
      vVar = b + (t - b) * (j + 0.5) / (this->height);
      this->pixelLoc[i][j][0] = -1 * dist * w[0] + uVar * u[0] + vVar * v[0];
      this->pixelLoc[i][j][1] = -1 * dist * w[1] + uVar * u[1] + vVar * v[1];
      this->pixelLoc[i][j][2] = -1 * dist * w[2] + uVar * u[2] + vVar * v[2];
    }
  }
}

float* scene::rayCast(ray r, int depth){
  float dat[3] = {0};
  float temp[3] = {0};
  float areaLight[3] = {0};
  float newDirec[3] = {0};
  float t = 0;
  int loc, k, m;
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_real_distribution<> lis(0.0, 1.0);
  float lightAlpha, lightBeta;
  ray nu = ray();
  if(depth < 5){
    for(k = 0; (unsigned int)k < surf.size(); k++){
      if(surf.at(k).detectCollision(&r)){
        loc = k;
      }
      for(k = 0; (unsigned int)k < lights.size(); k++){ //need to add normals
        float* pointHit[3];
        pointHit[0] = (r.getOrigin()[0] + r.getT() * r.getDirection()[0]);
        pointHit[1] = (r.getOrigin()[1] + r.getT() * r.getDirection()[1]);
        pointHit[2] = (r.getOrigin()[2] + r.getT() * r.getDirection()[2]);
        for(m = 0; (unsigned int)m < surf.size(); m++){
          if(m != loc){ //check all but current shape
            ray shadRay = ray();
            shadRay.setOrigin(pointHit);
            lightAlpha = lis(gen);
            lightBeta = lis(gen); //multiple samples?
            areaLight[0] = lights.at(k).getLocation()[0] + lightAlpha * lights.at(k).getA()[0] + lightBeta * lights.at(k).getB()[0];
            areaLight[1] = lights.at(k).getLocation()[1] + lightAlpha * lights.at(k).getA()[1] + lightBeta * lights.at(k).getB()[1];
            areaLight[2] = lights.at(k).getLocation()[2] + lightAlpha * lights.at(k).getA()[2] + lightBeta * lights.at(k).getB()[2];
            shadRay.setDirection(areaLight);
            if(surf.at(m).detectCollision(&shadRay)) shadow = true;
          }
        }
        if(!shadow){
          if(surf.at(loc).isSphere()){
            float* normal[3];
            normal[0] = ((r.getOrigin()[0] + r.getT() * r.getDirection()[0]) - surf.at(loc).getPos()[0]) / sqrt(powf((r.getOrigin()[0] + r.getT() * r.getDirection()[0]) - surf.at(loc).getPos()[0], 2) + powf((r.getOrigin()[1] + r.getT() * r.getDirection()[1]) - surf.at(loc).getPos()[1], 2) + powf((r.getOrigin()[2] + r.getT() * r.getDirection()[2]) - surf.at(loc).getPos()[2], 2));
            normal[1] = ((r.getOrigin()[1] + r.getT() * r.getDirection()[1]) - surf.at(loc).getPos()[1]) / sqrt(powf((r.getOrigin()[0] + r.getT() * r.getDirection()[0]) - surf.at(loc).getPos()[0], 2) + powf((r.getOrigin()[1] + r.getT() * r.getDirection()[1]) - surf.at(loc).getPos()[1], 2) + powf((r.getOrigin()[2] + r.getT() * r.getDirection()[2]) - surf.at(loc).getPos()[2], 2));
            normal[2] = ((r.getOrigin()[2] + r.getT() * r.getDirection()[2]) - surf.at(loc).getPos()[2]) / sqrt(powf((r.getOrigin()[0] + r.getT() * r.getDirection()[0]) - surf.at(loc).getPos()[0], 2) + powf((r.getOrigin()[1] + r.getT() * r.getDirection()[1]) - surf.at(loc).getPos()[1], 2) + powf((r.getOrigin()[2] + r.getT() * r.getDirection()[2]) - surf.at(loc).getPos()[2], 2));

            newDirec[0] = rTemp.getDirection()[0] - 2 * rTemp.dotProduct(rTemp.getDirection(), normal) * normal[0];
            newDirec[1] = rTemp.getDirection()[1] - 2 * rTemp.dotProduct(rTemp.getDirection(), normal) * normal[1];
            newDirec[2] = rTemp.getDirection()[2] - 2 * rTemp.dotProduct(rTemp.getDirection(), normal) * normal[2];

            nu.setOrigin(pointHit);
            nu.setDirection(newDirec);

            temp[0] = temp[0] + surf.at(loc).getDiffuse().getColor()[0] * lights.at(k).getColor().getColor()[0] * std::max(0, rTemp.dotProduct(lights.at(k).getLocation(), normal));
            temp[1] = temp[1] + surf.at(loc).getDiffuse().getColor()[1] * lights.at(k).getColor().getColor()[1] * std::max(0, rTemp.dotProduct(lights.at(k).getLocation(), normal));
            temp[2] = temp[2] + surf.at(loc).getDiffuse().getColor()[2] * lights.at(k).getColor().getColor()[2] * std::max(0, rTemp.dotProduct(lights.at(k).getLocation(), normal));

          } else {

            newDirec[0] = rTemp.getDirection()[0] - 2 * rTemp.dotProduct(rTemp.getDirection(), surf.at(loc).getNormal()) * normal[0];
            newDirec[1] = rTemp.getDirection()[1] - 2 * rTemp.dotProduct(rTemp.getDirection(), surf.at(loc).getNormal()) * normal[1];
            newDirec[2] = rTemp.getDirection()[2] - 2 * rTemp.dotProduct(rTemp.getDirection(), surf.at(loc).getNormal()) * normal[2];

            r.setOrigin(pointHit);
            r.setDirection(newDirec);

            temp[0] = temp[0] + surf.at(loc).getDiffuse().getColor()[0] * lights.at(k).getColor().getColor()[0] * std::max(0, rTemp.dotProduct(lights.at(k).getLocation(), surf.at(loc).getNormal()));
            temp[1] = temp[1] + surf.at(loc).getDiffuse().getColor()[1] * lights.at(k).getColor().getColor()[1] * std::max(0, rTemp.dotProduct(lights.at(k).getLocation(), surf.at(loc).getNormal()));
            temp[2] = temp[2] + surf.at(loc).getDiffuse().getColor()[2] * lights.at(k).getColor().getColor()[2] * std::max(0, rTemp.dotProduct(lights.at(k).getLocation(), surf.at(loc).getNormal()));

          }
        } else {
          temp[0] = 0.0;
          temp[1] = 0.0;
          temp[2] = 0.0;
        }
      }
      dat = rayCast(nu, depth + 1);

      dat[0] = dat[0] + temp[0];
      dat[1] = dat[1] + temp[1];
      dat[2] = dat[2] + temp[2];

      return dat;
    }
  } else return dat;
}

void scene::makeData(){
  this->data = new pixel*[this->height];
  int i, j, k, m, s, loc, depth = 0;
  float temp[3] = {0};
  float areaLight[3] = {0};
  float *w, *u, *v;
  ray r = ray(); //needed because my compilier throws a fit whenever i try to use static functions
  bool shadow = false;
  float anti[3], newDirec[3], dat[3];
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_real_distribution<> dis(-0.5, 0.5);
  std::uniform_real_distribution<> lis(0.0, 1.0);
  float lightAlpha, lightBeta;

  //calculate u, v, w
  w[0] = -1.0 * this->lookat[0] / sqrt(powf(this->lookat[0],2) + powf(this->lookat[1],2) + powf(this->lookat[2],2));
  w[1] = -1.0 * this->lookat[1] / sqrt(powf(this->lookat[0],2) + powf(this->lookat[1],2) + powf(this->lookat[2],2));
  w[2] = -1.0 * this->lookat[2] / sqrt(powf(this->lookat[0],2) + powf(this->lookat[1],2) + powf(this->lookat[2],2));

  u = r.crossProduct((float*)this->up, w);
  u[0] = u[0] / sqrt(powf(u[0],2) + powf(u[1],2) + powf(u[2],2));
  u[1] = u[1] / sqrt(powf(u[0],2) + powf(u[1],2) + powf(u[2],2));
  u[2] = u[2] / sqrt(powf(u[0],2) + powf(u[1],2) + powf(u[2],2));

  v = r.crossProduct(w, u);

  float dist = powf((powf(this->eye[0] - this->lookat[0], 2)) + (powf(this->eye[1] - this->lookat[1], 2)) + (powf(this->eye[2] - this->lookat[2], 2)), 0.5);

  for(i = 0; i < this->height; i++){
    this->data[i] = new pixel[width];
  }

  createPixelLoc(w, u, v, dist);

  for(i = 0; i < this->height; i++){
    for(j = 0; j < this->width; j++){
      for(s = 0; s < this->samples; s++){
        //send ray for this pixel
        anti[0] = this->pixelLoc[i][j][0] + dis(gen);
        anti[1] = this->pixelLoc[i][j][1] + dis(gen);
        anti[2] = this->pixelLoc[i][j][2] + dis(gen);
        ray rTemp = ray();
        rTemp.setOrigin(this->eye);
        rTemp.setDirection(anti);
        //calculate collision
        for(k = 0; (unsigned int)k < surf.size(); k++){
          if(surf.at(k).detectCollision(&rTemp)){
            loc = k;
          }
        }
        //calculate color
        for(k = 0; (unsigned int)k < lights.size(); k++){ //need to add normals
          float* pointHit[3];
          pointHit[0] = (this->eye[0] + rTemp.getT() * anti[0]);
          pointHit[1] = (this->eye[1] + rTemp.getT() * anti[1]);
          pointHit[2] = (this->eye[2] + rTemp.getT() * anti[2]);
          for(m = 0; (unsigned int)m < surf.size(); m++){
            if(m != loc){ //check all but current shape
              ray shadRay = ray();
              shadRay.setOrigin(pointHit);
              lightAlpha = lis(gen);
              lightBeta = lis(gen); //multiple samples?
              areaLight[0] = lights.at(k).getLocation()[0] + lightAlpha * lights.at(k).getA()[0] + lightBeta * lights.at(k).getB()[0];
              areaLight[1] = lights.at(k).getLocation()[1] + lightAlpha * lights.at(k).getA()[1] + lightBeta * lights.at(k).getB()[1];
              areaLight[2] = lights.at(k).getLocation()[2] + lightAlpha * lights.at(k).getA()[2] + lightBeta * lights.at(k).getB()[2];
              shadRay.setDirection(areaLight);
              if(surf.at(m).detectCollision(&shadRay)) shadow = true;
            }
          }
          if(!shadow){
            if(surf.at(loc).isSphere()){
              float* normal[3];
              normal[0] = ((this->eye[0] + rTemp.getT() * anti[i][j][0]) - surf.at(loc).getPos()[0]) / sqrt(powf((this->eye[0] + rTemp.getT() * this->pixelLoc[i][j][0]) - surf.at(loc).getPos()[0], 2) + powf((this->eye[1] + rTemp.getT() * this->pixelLoc[i][j][1]) - surf.at(loc).getPos()[1], 2) + powf((this->eye[2] + rTemp.getT() * this->pixelLoc[i][j][2]) - surf.at(loc).getPos()[2], 2));
              normal[1] = ((this->eye[1] + rTemp.getT() * anti[i][j][1]) - surf.at(loc).getPos()[1]) / sqrt(powf((this->eye[0] + rTemp.getT() * this->pixelLoc[i][j][0]) - surf.at(loc).getPos()[0], 2) + powf((this->eye[1] + rTemp.getT() * this->pixelLoc[i][j][1]) - surf.at(loc).getPos()[1], 2) + powf((this->eye[2] + rTemp.getT() * this->pixelLoc[i][j][2]) - surf.at(loc).getPos()[2], 2));
              normal[2] = ((this->eye[2] + rTemp.getT() * anti[i][j][2]) - surf.at(loc).getPos()[2]) / sqrt(powf((this->eye[0] + rTemp.getT() * this->pixelLoc[i][j][0]) - surf.at(loc).getPos()[0], 2) + powf((this->eye[1] + rTemp.getT() * this->pixelLoc[i][j][1]) - surf.at(loc).getPos()[1], 2) + powf((this->eye[2] + rTemp.getT() * this->pixelLoc[i][j][2]) - surf.at(loc).getPos()[2], 2));

              newDirec[0] = rTemp.getDirection()[0] - 2 * rTemp.dotProduct(rTemp.getDirection(), normal) * normal[0];
              newDirec[1] = rTemp.getDirection()[1] - 2 * rTemp.dotProduct(rTemp.getDirection(), normal) * normal[1];
              newDirec[2] = rTemp.getDirection()[2] - 2 * rTemp.dotProduct(rTemp.getDirection(), normal) * normal[2];

              r.setOrigin(pointHit);
              r.setDirection(newDirec);

              temp[0] = temp[0] + surf.at(loc).getDiffuse().getColor()[0] * lights.at(k).getColor().getColor()[0] * std::max(0, rTemp.dotProduct(lights.at(k).getLocation(), normal));
              temp[1] = temp[1] + surf.at(loc).getDiffuse().getColor()[1] * lights.at(k).getColor().getColor()[1] * std::max(0, rTemp.dotProduct(lights.at(k).getLocation(), normal));
              temp[2] = temp[2] + surf.at(loc).getDiffuse().getColor()[2] * lights.at(k).getColor().getColor()[2] * std::max(0, rTemp.dotProduct(lights.at(k).getLocation(), normal));
            } else {

              newDirec[0] = rTemp.getDirection()[0] - 2 * rTemp.dotProduct(rTemp.getDirection(), surf.at(loc).getNormal()) * normal[0];
              newDirec[1] = rTemp.getDirection()[1] - 2 * rTemp.dotProduct(rTemp.getDirection(), surf.at(loc).getNormal()) * normal[1];
              newDirec[2] = rTemp.getDirection()[2] - 2 * rTemp.dotProduct(rTemp.getDirection(), surf.at(loc).getNormal()) * normal[2];

              r.setOrigin(pointHit);
              r.setDirection(newDirec);

              temp[0] = temp[0] + surf.at(loc).getDiffuse().getColor()[0] * lights.at(k).getColor().getColor()[0] * std::max(0, rTemp.dotProduct(lights.at(k).getLocation(), surf.at(loc).getNormal()));
              temp[1] = temp[1] + surf.at(loc).getDiffuse().getColor()[1] * lights.at(k).getColor().getColor()[1] * std::max(0, rTemp.dotProduct(lights.at(k).getLocation(), surf.at(loc).getNormal()));
              temp[2] = temp[2] + surf.at(loc).getDiffuse().getColor()[2] * lights.at(k).getColor().getColor()[2] * std::max(0, rTemp.dotProduct(lights.at(k).getLocation(), surf.at(loc).getNormal()));
            }
          } else {
            temp[0] = 0.0;
            temp[1] = 0.0;
            temp[2] = 0.0;
          }
          shadow = false;
        }
        dat = rayCast(r, depth + 1);

        temp[0] = dat[0] + temp[0];
        temp[1] = dat[1] + temp[1];
        temp[2] = dat[2] + temp[2];
      }
      temp[0] = temp[0] / this->samples;
      temp[1] = temp[1] / this->samples;
      temp[2] = temp[2] / this->samples;

      data[i][j].setColor(dat);
    }
  }
}

void moveLeft(){
  ray temp = ray();
  this->eye[0] = this->eye[0] - 0.5;
  this->eye[2] = this->eye[2] + 0.5;
}

void moveRight(){
  ray temp = ray():
  this->eye[0] = this->eye[0] + 0.5;
  this->eye[2] = this->eye[2] + 0.5;
}
