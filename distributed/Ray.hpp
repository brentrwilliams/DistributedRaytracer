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

typedef struct
{
   float l;
   float r;
   float b;
   float t;
   glm::vec3 u;
   glm::vec3 v;
   glm::vec3 w;
   int imgWidth;
   int imgHeight;
   int i; // Column index of image
   int j; // Row index of image
   glm::vec3 p_0;
} RayCalcInfo;

class Ray
{
   public:
      Ray();
      Ray(glm::vec3 p, glm::vec3 d);
      Ray(const Ray& ray);
      Ray(glm::vec3 p, glm::vec3 d, float ior);
      friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
      void calculateRay(RayCalcInfo rayCalcInfo, int x, int y);
      void toObjectSpace(glm::mat4 invTrans);

      glm::vec3 p;
      glm::vec3 d; 
      float ior; //ior of the space before intersection
};

#endif
