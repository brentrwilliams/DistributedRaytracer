/**
 * Raytracer.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef IMAGE_H
#define IMAGE_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 

using namespace glm; 
using namespace std;

typedef struct {
   char  idlength;
   char  colourmaptype;
   char  datatypecode;
   short int colourmaporigin;
   short int colourmaplength;
   char  colourmapdepth;
   short int x_origin;
   short int y_origin;
   short width;
   short height;
   char  bitsperpixel;
   char  imagedescriptor;
} TGAHeader;

class Image 
{
   public:
      float **r;
      float **g;
      float **b;
      int width;
      int height;
      char filename[256];
      
      Image();
      Image(int width, int height);
      void allocateImage(int width, int height);
      void readTGA(char *filename);
      void writeTGA(char *filename);
      void scaleColors();
      vec3 getColor(int x, int y);      
};

#endif
