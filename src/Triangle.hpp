//Triangle.h

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <iostream>
#include <fstream>
#include <string.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Ray.hpp"
#include "BoundingBox.hpp"
#include "RaytracerObject.hpp"

#define MAX_CHARS_PER_LINE 512

class Triangle : public RaytracerObject
{
   public:
      glm::vec3 v1;
      glm::vec3 v2;
      glm::vec3 v3;
      
      glm::vec2 uv1;
      glm::vec2 uv2;
      glm::vec2 uv3;
      
      BoundingBox boundingBox;
      
      Triangle();
      Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3);
      friend std::ostream& operator<<(std::ostream& os, const Triangle& triangle);
      bool intersect(Ray ray, float *t);
      glm::vec3 getNormal(glm::vec3 pt);
      void calculateBoundingBox();
      glm::vec2 getUV(glm::vec3 pt);

};

bool xAxisSort(Triangle tri1, Triangle tri2);
bool yAxisSort(Triangle tri1, Triangle tri2);
bool zAxisSort(Triangle tri1, Triangle tri2);

#endif
