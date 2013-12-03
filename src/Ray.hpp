/**
 * Ray.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef RAY_H
#define RAY_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
using namespace glm;

typedef struct
{
   float l;
   float r;
   float b;
   float t;
   vec3 u;
   vec3 v;
   vec3 w;
   int imgWidth;
   int imgHeight;
   int i; // Column index of image
   int j; // Row index of image
   vec3 p_0;
} RayCalcInfo;

class Ray
{
   public:
      Ray();
      Ray(vec3 p, vec3 d);
      Ray(const Ray& ray);
      Ray(vec3 p, vec3 d, float ior);
      friend ostream& operator<<(ostream& os, const Ray& ray);
      void calculateRay(RayCalcInfo rayCalcInfo, int x, int y);
      void toObjectSpace(mat4 invTrans);

      vec3 p;
      vec3 d; 
      float ior; //ior of the space before intersection
};

#endif
