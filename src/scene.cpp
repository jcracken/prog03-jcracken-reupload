#include "scene.h"

scene::scene(){ //constructor
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

float** scene::returnData(){ //converts data stored locally into a 2D float array and returns it
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

int scene::returnWidth(){ //returns width
  return this->width;
}

int scene::returnHeight(){ //returns height
  return this->height;
}

float* scene::returnEye(){ //returns eye
  return this->eye;
}

float* scene::returnLookAt(){ //returns lookat
  return this->lookat;
}

float* scene::returnUp(){ //returns up
  return this->up;
}

float scene::returnAngle(){ //returns angle
  return this->angle;
}

///This takes in a filename (name), opens it, and populates variables based on that file's contents

void scene::acquireData(std::string name){

  std::ifstream input(name, std::ifstream::in); //open file
  std::string parse; //used for parsing
  bool follow = false; //used for parsing
  char type = '\0'; //type of data being read

  light lTemp = light(); //used for parsing

  float temp[3]; //used for parsing
  int line = 0; //used for parsing
  int i = 0; //used for parsing

  //verifies file existence
  if(!(input.is_open())){
    std::cout << "File not found; try excluding the filename extension" << std::endl;
    exit(EXIT_FAILURE);
  }
  while(!input.eof()){
	  if (getline(input, parse)) { //if file line is empty, skip it
		  if (parse.at(0) >= 65 && parse.at(0) <= 122) { //if line starts with char, figure out what data on that line
			  type = parse.at(0);
			  follow = false;
		  }
		  else follow = true; //if it doesn't start with a char, it's adding to the last line (or two lines ago)
		  std::istringstream iss(parse); //convert the line to a string stream to parse data from it
		  switch (type) { //based on the type of data being read
			  case 'e': //eye
				  iss >> eye[0];
				  iss >> eye[1];
				  iss >> eye[2];
			  break;
			  case 'l': //lookat
				  iss >> lookat[0];
				  iss >> lookat[1];
				  iss >> lookat[2];
			  break;
			  case 'u': //up
				  iss >> up[0];
				  iss >> up[1];
				  iss >> up[2];
			  break;
			  case 'f': //fov
				  iss >> angle;
			  break;
			  case 'i': //image dimensions
				  iss >> width;
				  iss >> height;
			  break;
			  case 'L': //light
				  iss >> temp[0];
				  iss >> temp[1];
				  iss >> temp[2];
				  if (!follow) {
					  lTemp.setLoc(temp); //first read in location
				  }
				  else {
					  lTemp.setCol(temp); //next line is color, so read in that second
					  lights.push_back(lTemp);
				  }
			  break;
			  case 'P': //plane
				  iss >> temp[0];
				  if (line != 4) { //last line only has one value to read in
					  iss >> temp[1];
					  iss >> temp[2];
				  }
				  if (!follow) {
					  surf.push_back(new plane()); //add new plane to list of surfaces
					  surf.at(i)->setPos(temp); //set position to what was read in
					  iss >> temp[0];
					  iss >> temp[1];
					  iss >> temp[2];
					  surf.at(i)->setNormal(temp); //read in normal and save it
					  line = 1;
				  }
				  else {
					  if (line == 1) {
						  surf.at(i)->setAmbient(temp); //store ambient
						  line = 2;
					  }
					  else if (line == 2) {
						  surf.at(i)->setDiffuse(temp); //store diffuse
						  line = 3;
					  }
					  else if (line == 3) {
						  surf.at(i)->setSpecular(temp); //store specular
						  line = 4;
					  }
					  else {
						  surf.at(i)->setPhong(temp[0]); //store phong
						  line = 0;
						  i++;
					  } //line denotes how many lines of the current plane data has been read in.
				  }
			  break;
			  case 'S': //this is sphere; very similar to the last case, but with a sphere instead
				  iss >> temp[0];
				  if (line != 4) {
					  iss >> temp[1];
					  iss >> temp[2];
				  }
				  if (!follow) {
					  surf.push_back(new sphere());
					  surf.at(i)->setPos(temp);
					  iss >> temp[0];
					  surf.at(i)->setRadius(temp[0]); //instead of normal, there's a radius
					  line = 1;
				  }
				  else {
					  if (line == 1) {
						  surf.at(i)->setAmbient(temp);
						  line = 2;
					  }
					  else if (line == 2) {
						  surf.at(i)->setDiffuse(temp);
						  line = 3;
					  }
					  else if (line == 3) {
						  surf.at(i)->setSpecular(temp);
						  line = 4;
					  }
					  else {
						  surf.at(i)->setPhong(temp[0]);
						  line = 0;
						  surf.at(i)->setType();
						  i++; //i is the current location in surf--it starts at 0 and goes up after we add a new surf
					  }
				  }
				  break;
			  case 's': //read in samples for anti-aliasing
				  iss >> this->samples;
				  break;
			  case 'A': //area light
				  iss >> temp[0];
				  iss >> temp[1];
				  iss >> temp[2];
				  if (!follow) {
					  lTemp.setLoc(temp);
					  iss >> temp[0];
					  iss >> temp[1];
					  iss >> temp[2];
					  lTemp.setA(temp); //A vector
					  iss >> temp[0];
					  iss >> temp[1];
					  iss >> temp[2];
					  lTemp.setB(temp); //B vector
				  }
				  else {
					  lTemp.setCol(temp); //color
					  lights.push_back(lTemp);
				  }
				  break;
			  default: //there's a line that doesn't make any sense
				  std::cout << "input file malformed" << std::endl;
				  exit(EXIT_FAILURE);
			  break;
		}
    }
  }
  input.close();
}


///This function populates the location of every pixel, for the ray tracing
/// u, w, v are the basis vectors; dist is the distance between eye and lookat

void scene::createPixelLoc(float* w, float* u, float* v, float dist){
  int i, j; //for loops
  float uVar, vVar, r, t, l, b; //used in calculations
  ray thisShouldBeStatic = ray(); //needed because my compilier throws a fit whenever i try to use static functions
  this->pixelLoc = new float**[this->height]; //c++ hates non-static vars used in initialization, so this is the compromise
  for(i = 0; i < this->height; i++){
    this->pixelLoc[i] = new float*[this->width];
  }

  float imageHeight = std::tan(this->angle / 2.0) * dist; //calculate image height
  float imageWidth = std::tan((this->angle * this->width / this->height) / 2.0) * dist; //calculate image width

  r = thisShouldBeStatic.dotProduct(this->lookat, u) + imageWidth / 2.0; //calculations for vars used in pixel locs
  l = thisShouldBeStatic.dotProduct(this->lookat, u) - imageWidth / 2.0;
  t = thisShouldBeStatic.dotProduct(this->lookat, v) + imageHeight / 2.0;
  b = thisShouldBeStatic.dotProduct(this->lookat, v) - imageHeight / 2.0;

  for(i = 0; i < this->height; i++){ //populate the array with pixel locations
    for(j = 0; j < this->height; j++){

      uVar = l + (r - l) * (i + 0.5) / (this->width);
      vVar = b + (t - b) * (j + 0.5) / (this->height);

	  //because u, v, w are updated every time eye is, this should work fine for DoF afaik

      this->pixelLoc[i][j][0] = -1 * dist * w[0] + uVar * u[0] + vVar * v[0];
      this->pixelLoc[i][j][1] = -1 * dist * w[1] + uVar * u[1] + vVar * v[1];
      this->pixelLoc[i][j][2] = -1 * dist * w[2] + uVar * u[2] + vVar * v[2];
    }
  }
}

///this is the recursive raycast function

float* scene::rayCast(ray r, int depth){

  float* dat; //data that will be returned

  float temp[3] = {0}; //used as a temp location
  float areaLight[3] = {0}; //used for shadow calculation
  float newDirec[3] = {0}; //used for recursion
  int loc, k, m; //used for loops
  bool shadow = false; //used for shadows

  //used to randomly choose points within the arealight for soft shadows
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_real_distribution<> lis(0.0, 1.0);
  float lightAlpha, lightBeta;

  ray nu = ray(); //ray used for recursion
  if(depth < 5){ //depth of recursion
    for(k = 0; (unsigned int)k < surf.size(); k++){ //for every surface, see if it collides
      if(surf.at(k)->detectCollision(&r)){
        loc = k; //if it does collide, and it's the first to collide, save it
      }
      for(k = 0; (unsigned int)k < lights.size(); k++){ //for each light, calculate color
        float pointHit[3];
        pointHit[0] = (r.getOrigin()[0] + r.getT() * r.getDirection()[0]);
        pointHit[1] = (r.getOrigin()[1] + r.getT() * r.getDirection()[1]);
        pointHit[2] = (r.getOrigin()[2] + r.getT() * r.getDirection()[2]);

        for(m = 0; (unsigned int)m < surf.size(); m++){ //used to check for shadows
          if(m != loc){ //check all but current shape
            ray shadRay = ray(); //ray used to trace back to light source to see if there are any collisions
            shadRay.setOrigin(pointHit); //original collision location

            lightAlpha = lis(gen); //randomly gen values
            lightBeta = lis(gen);

            areaLight[0] = lights.at(k).getLoc()[0] + lightAlpha * lights.at(k).getA()[0] + lightBeta * lights.at(k).getB()[0];
            areaLight[1] = lights.at(k).getLoc()[1] + lightAlpha * lights.at(k).getA()[1] + lightBeta * lights.at(k).getB()[1];
            areaLight[2] = lights.at(k).getLoc()[2] + lightAlpha * lights.at(k).getA()[2] + lightBeta * lights.at(k).getB()[2];

            shadRay.setDirection(areaLight); //arealight is a point in the light, we are heading in that direction
            if(surf.at(m)->detectCollision(&shadRay)) shadow = true; //if it collides with anything, there is a shadow
          }
        }
        if(!shadow){ //if no shadow
          if(surf.at(loc)->isSphere()){

            float normal[3]; //find normal for sphere
            normal[0] = ((r.getOrigin()[0] + r.getT() * r.getDirection()[0]) - surf.at(loc)->getPos()[0]) / sqrt(powf((r.getOrigin()[0] + r.getT() * r.getDirection()[0]) - surf.at(loc)->getPos()[0], 2) + powf((r.getOrigin()[1] + r.getT() * r.getDirection()[1]) - surf.at(loc)->getPos()[1], 2) + powf((r.getOrigin()[2] + r.getT() * r.getDirection()[2]) - surf.at(loc)->getPos()[2], 2));
            normal[1] = ((r.getOrigin()[1] + r.getT() * r.getDirection()[1]) - surf.at(loc)->getPos()[1]) / sqrt(powf((r.getOrigin()[0] + r.getT() * r.getDirection()[0]) - surf.at(loc)->getPos()[0], 2) + powf((r.getOrigin()[1] + r.getT() * r.getDirection()[1]) - surf.at(loc)->getPos()[1], 2) + powf((r.getOrigin()[2] + r.getT() * r.getDirection()[2]) - surf.at(loc)->getPos()[2], 2));
            normal[2] = ((r.getOrigin()[2] + r.getT() * r.getDirection()[2]) - surf.at(loc)->getPos()[2]) / sqrt(powf((r.getOrigin()[0] + r.getT() * r.getDirection()[0]) - surf.at(loc)->getPos()[0], 2) + powf((r.getOrigin()[1] + r.getT() * r.getDirection()[1]) - surf.at(loc)->getPos()[1], 2) + powf((r.getOrigin()[2] + r.getT() * r.getDirection()[2]) - surf.at(loc)->getPos()[2], 2));

            newDirec[0] = r.getDirection()[0] - 2 * r.dotProduct(r.getDirection(), normal) * normal[0]; //calculate new dir for recursive ray
            newDirec[1] = r.getDirection()[1] - 2 * r.dotProduct(r.getDirection(), normal) * normal[1];
            newDirec[2] = r.getDirection()[2] - 2 * r.dotProduct(r.getDirection(), normal) * normal[2];

            nu.setOrigin(pointHit); //new ray for recursion
            nu.setDirection(newDirec);

            temp[0] = temp[0] + surf.at(loc)->getSpecular().getColor()[0] * lights.at(k).getCol().getColor()[0] * std::max((float)0.0, r.dotProduct(lights.at(k).getLoc(), normal)); //calculate current color at this location
            temp[1] = temp[1] + surf.at(loc)->getSpecular().getColor()[1] * lights.at(k).getCol().getColor()[1] * std::max((float)0.0, r.dotProduct(lights.at(k).getLoc(), normal));
            temp[2] = temp[2] + surf.at(loc)->getSpecular().getColor()[2] * lights.at(k).getCol().getColor()[2] * std::max((float)0.0, r.dotProduct(lights.at(k).getLoc(), normal));

          } else { //the same as above, but for a plane

            newDirec[0] = r.getDirection()[0] - 2 * r.dotProduct(r.getDirection(), surf.at(loc)->getNormal()) * surf.at(loc)->getNormal()[0];
            newDirec[1] = r.getDirection()[1] - 2 * r.dotProduct(r.getDirection(), surf.at(loc)->getNormal()) * surf.at(loc)->getNormal()[1];
            newDirec[2] = r.getDirection()[2] - 2 * r.dotProduct(r.getDirection(), surf.at(loc)->getNormal()) * surf.at(loc)->getNormal()[2];

            r.setOrigin(pointHit);
            r.setDirection(newDirec);

            temp[0] = temp[0] + surf.at(loc)->getSpecular().getColor()[0] * lights.at(k).getCol().getColor()[0] * std::max((float)0.0, r.dotProduct(lights.at(k).getLoc(), surf.at(loc)->getNormal()));
            temp[1] = temp[1] + surf.at(loc)->getSpecular().getColor()[1] * lights.at(k).getCol().getColor()[1] * std::max((float)0.0, r.dotProduct(lights.at(k).getLoc(), surf.at(loc)->getNormal()));
            temp[2] = temp[2] + surf.at(loc)->getSpecular().getColor()[2] * lights.at(k).getCol().getColor()[2] * std::max((float)0.0, r.dotProduct(lights.at(k).getLoc(), surf.at(loc)->getNormal()));

          }
        } else { //if shadow, the pixel is black
          temp[0] = 0.0;
          temp[1] = 0.0;
          temp[2] = 0.0;
        }
      }
    }
    dat = rayCast(nu, depth + 1); //recursion

    dat[0] = dat[0] + temp[0]; //add data to data that will be returned
    dat[1] = dat[1] + temp[1];
    dat[2] = dat[2] + temp[2];
  }
  return dat;
}

void scene::makeData(){ //this is the rest of the ray cast code

  this->data = new pixel*[this->height]; //c++ hates init with non-static vars

  int i, j, k, m, s, loc; //used in loops and other temp ways
  float temp[3] = {0}; //temp data storage
  float areaLight[3] = {0}; //used for lights
  float normal[3]; //used for spheres
  float* w = new float[3]; //w from basis
  float *u, *v, *dat; //basis, stores data

  ray r = ray(); //needed because my compilier throws a fit whenever i try to use static functions

  bool shadow = false; //shadow or not
  float anti[3], newDirec[3]; //anti aliaising and ray for recursion

  std::random_device rd; //random generation for shadows and antialiasing
  std::mt19937 gen{rd()};
  std::uniform_real_distribution<> dis(-0.5, 0.5);
  std::uniform_real_distribution<> lis(0.0, 1.0);
  float lightAlpha, lightBeta, R0; //refraction or reflection

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

  for(i = 0; i < this->height; i++){ //cuz c++ hates non-static init
    this->data[i] = new pixel[width];
  }

  createPixelLoc(w, u, v, dist); //creates 2d array with all of the pixel locations

  for(i = 0; i < this->height; i++){ //iterate through all pixels
    for(j = 0; j < this->width; j++){
      for(s = 0; s < this->samples; s++){ //do each pixel s times
        //send ray for this pixel
        anti[0] = this->pixelLoc[i][j][0] + dis(gen);
        anti[1] = this->pixelLoc[i][j][1] + dis(gen);
        anti[2] = this->pixelLoc[i][j][2] + dis(gen);
        ray rTemp = ray();
        rTemp.setOrigin(this->eye);
        rTemp.setDirection(anti);
        //calculate collision
        for(k = 0; (unsigned int)k < surf.size(); k++){
          if(surf.at(k)->detectCollision(&rTemp)){
            loc = k;
          }
        }
        //calculate color---pretty much the rest maps to the ray recursion function
        for(k = 0; (unsigned int)k < lights.size(); k++){
          float pointHit[3];
          pointHit[0] = (this->eye[0] + rTemp.getT() * anti[0]);
          pointHit[1] = (this->eye[1] + rTemp.getT() * anti[1]);
          pointHit[2] = (this->eye[2] + rTemp.getT() * anti[2]);
          for(m = 0; (unsigned int)m < surf.size(); m++){
            if(m != loc){ //check all but current shape
              ray shadRay = ray();
              shadRay.setOrigin(pointHit);
              lightAlpha = lis(gen);
              lightBeta = lis(gen); //multiple samples?
              areaLight[0] = lights.at(k).getLoc()[0] + lightAlpha * lights.at(k).getA()[0] + lightBeta * lights.at(k).getB()[0];
              areaLight[1] = lights.at(k).getLoc()[1] + lightAlpha * lights.at(k).getA()[1] + lightBeta * lights.at(k).getB()[1];
              areaLight[2] = lights.at(k).getLoc()[2] + lightAlpha * lights.at(k).getA()[2] + lightBeta * lights.at(k).getB()[2];
              shadRay.setDirection(areaLight);
              if(surf.at(m)->detectCollision(&shadRay)) shadow = true;
            }
          }
          if(!shadow){
            R0 = powf((surf.at(loc)->getPhong() - 1.0) / (surf.at(loc)->getPhong() + 1.0), 2.0); //for reflection/refraction
            if(surf.at(loc)->isSphere()){
              normal[0] = ((this->eye[0] + rTemp.getT() * anti[0]) - surf.at(loc)->getPos()[0]) / sqrt(powf((this->eye[0] + rTemp.getT() * anti[0]) - surf.at(loc)->getPos()[0], 2.0) + powf((this->eye[1] + rTemp.getT() * anti[1]) - surf.at(loc)->getPos()[1], 2.0) + powf((this->eye[2] + rTemp.getT() * anti[2]) - surf.at(loc)->getPos()[2], 2.0));
              normal[1] = ((this->eye[1] + rTemp.getT() * anti[1]) - surf.at(loc)->getPos()[1]) / sqrt(powf((this->eye[0] + rTemp.getT() * anti[0]) - surf.at(loc)->getPos()[0], 2.0) + powf((this->eye[1] + rTemp.getT() * anti[1]) - surf.at(loc)->getPos()[1], 2.0) + powf((this->eye[2] + rTemp.getT() * anti[2]) - surf.at(loc)->getPos()[2], 2.0));
              normal[2] = ((this->eye[2] + rTemp.getT() * anti[2]) - surf.at(loc)->getPos()[2]) / sqrt(powf((this->eye[0] + rTemp.getT() * anti[0]) - surf.at(loc)->getPos()[0], 2.0) + powf((this->eye[1] + rTemp.getT() * anti[1]) - surf.at(loc)->getPos()[1], 2.0) + powf((this->eye[2] + rTemp.getT() * anti[2]) - surf.at(loc)->getPos()[2], 2.0));

              if(surf.at(loc)->getPhong() != 0.0){ //reflection/refraction
                r.setOrigin(pointHit);
                if(lis(gen) < R0){
                  newDirec[0] = rTemp.getDirection()[0] - 2 * rTemp.dotProduct(rTemp.getDirection(), normal) * normal[0];
                  newDirec[1] = rTemp.getDirection()[1] - 2 * rTemp.dotProduct(rTemp.getDirection(), normal) * normal[1];
                  newDirec[2] = rTemp.getDirection()[2] - 2 * rTemp.dotProduct(rTemp.getDirection(), normal) * normal[2];
                } else {
                  newDirec[0] = rTemp.getDirection()[0] - rTemp.dotProduct(rTemp.getDirection(), normal) * normal[0] / surf.at(loc)->getPhong();
                  newDirec[1] = rTemp.getDirection()[1] - rTemp.dotProduct(rTemp.getDirection(), normal) * normal[1] / surf.at(loc)->getPhong();
                  newDirec[2] = rTemp.getDirection()[2] - rTemp.dotProduct(rTemp.getDirection(), normal) * normal[2] / surf.at(loc)->getPhong();

                  newDirec[0] = newDirec[0] - normal[0] * sqrt(1 - ((1 - powf(rTemp.dotProduct(rTemp.getDirection(), normal), 2.0)) / powf(surf.at(loc)->getPhong(), 2.0)));
                  newDirec[1] = newDirec[1] - normal[1] * sqrt(1 - ((1 - powf(rTemp.dotProduct(rTemp.getDirection(), normal), 2.0)) / powf(surf.at(loc)->getPhong(), 2.0)));
                  newDirec[2] = newDirec[2] - normal[2] * sqrt(1 - ((1 - powf(rTemp.dotProduct(rTemp.getDirection(), normal), 2.0)) / powf(surf.at(loc)->getPhong(), 2.0)));
                }
                r.setDirection(newDirec);
              }

              temp[0] = temp[0] + surf.at(loc)->getDiffuse().getColor()[0] * lights.at(k).getCol().getColor()[0] * std::max((float)0.0, rTemp.dotProduct(lights.at(k).getLoc(), normal));
              temp[1] = temp[1] + surf.at(loc)->getDiffuse().getColor()[1] * lights.at(k).getCol().getColor()[1] * std::max((float)0.0, rTemp.dotProduct(lights.at(k).getLoc(), normal));
              temp[2] = temp[2] + surf.at(loc)->getDiffuse().getColor()[2] * lights.at(k).getCol().getColor()[2] * std::max((float)0.0, rTemp.dotProduct(lights.at(k).getLoc(), normal));
            } else {

              if(surf.at(loc)->getPhong() != 0.0){ //see above
                r.setOrigin(pointHit);
                if(lis(gen) < R0){
                  newDirec[0] = rTemp.getDirection()[0] - 2 * rTemp.dotProduct(rTemp.getDirection(), surf.at(loc)->getNormal()) * normal[0];
                  newDirec[1] = rTemp.getDirection()[1] - 2 * rTemp.dotProduct(rTemp.getDirection(), surf.at(loc)->getNormal()) * normal[1];
                  newDirec[2] = rTemp.getDirection()[2] - 2 * rTemp.dotProduct(rTemp.getDirection(), surf.at(loc)->getNormal()) * normal[2];
                } else {
                  newDirec[0] = rTemp.getDirection()[0] - rTemp.dotProduct(rTemp.getDirection(), surf.at(loc)->getNormal()) * surf.at(loc)->getNormal()[0] / surf.at(loc)->getPhong();
                  newDirec[1] = rTemp.getDirection()[1] - rTemp.dotProduct(rTemp.getDirection(), surf.at(loc)->getNormal()) * surf.at(loc)->getNormal()[1] / surf.at(loc)->getPhong();
                  newDirec[2] = rTemp.getDirection()[2] - rTemp.dotProduct(rTemp.getDirection(), surf.at(loc)->getNormal()) * surf.at(loc)->getNormal()[2] / surf.at(loc)->getPhong();

                  newDirec[0] = newDirec[0] - surf.at(loc)->getNormal()[0] * sqrt(1 - ((1 - powf(rTemp.dotProduct(rTemp.getDirection(), surf.at(loc)->getNormal()), 2.0)) / powf(surf.at(loc)->getPhong(), 2.0)));
                  newDirec[1] = newDirec[1] - surf.at(loc)->getNormal()[1] * sqrt(1 - ((1 - powf(rTemp.dotProduct(rTemp.getDirection(), surf.at(loc)->getNormal()), 2.0)) / powf(surf.at(loc)->getPhong(), 2.0)));
                  newDirec[2] = newDirec[2] - surf.at(loc)->getNormal()[2] * sqrt(1 - ((1 - powf(rTemp.dotProduct(rTemp.getDirection(), surf.at(loc)->getNormal()), 2.0)) / powf(surf.at(loc)->getPhong(), 2.0)));
                }
                r.setDirection(newDirec);
              }

              temp[0] = temp[0] + surf.at(loc)->getDiffuse().getColor()[0] * lights.at(k).getCol().getColor()[0] * std::max((float)0.0, rTemp.dotProduct(lights.at(k).getLoc(), surf.at(loc)->getNormal()));
              temp[1] = temp[1] + surf.at(loc)->getDiffuse().getColor()[1] * lights.at(k).getCol().getColor()[1] * std::max((float)0.0, rTemp.dotProduct(lights.at(k).getLoc(), surf.at(loc)->getNormal()));
              temp[2] = temp[2] + surf.at(loc)->getDiffuse().getColor()[2] * lights.at(k).getCol().getColor()[2] * std::max((float)0.0, rTemp.dotProduct(lights.at(k).getLoc(), surf.at(loc)->getNormal()));
            }
          } else {
            temp[0] = 0.0;
            temp[1] = 0.0;
            temp[2] = 0.0;
          }
          shadow = false;
        }
        if(surf.at(loc)->getPhong() != 0.0){
          dat = rayCast(r, 1);

          temp[0] = dat[0] + temp[0];
          temp[1] = dat[1] + temp[1];
          temp[2] = dat[2] + temp[2];
        }
      }
      temp[0] = temp[0] / this->samples;
      temp[1] = temp[1] / this->samples;
      temp[2] = temp[2] / this->samples;

      data[i][j].setColor(dat);
    }
  }
}

void scene::moveLeft(){ //move the eye left and forward
  ray temp = ray();
  this->eye[0] = this->eye[0] - 0.5;
  this->eye[2] = this->eye[2] + 0.5;
}

void scene::moveRight(){ //move the eye left and forward
  ray temp = ray();
  this->eye[0] = this->eye[0] + 0.5;
  this->eye[2] = this->eye[2] + 0.5;
}
