/**
 * BoundingBox.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

#include <ostream>
#include <iostream>
#include <fstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Ray.hpp"

#define MAX_CHARS_PER_LINE 512
#define MAXIMUM_FLOAT 1000000000
#define MINIMUM_FLOAT -1000000000

class BoundingBox
{
   public:
      glm::vec3 mins;
      glm::vec3 maxs;
      glm::vec3 corner[8];
      glm::vec3 center;
      
      BoundingBox();
      BoundingBox(glm::vec3 mins, glm::vec3 maxs);
      BoundingBox(BoundingBox bb1, BoundingBox bb2);
      void calculateCorners();
      bool intersect(Ray ray);
      void transform(glm::mat4 trans);
      void calculateCenter();
      friend std::ostream &operator<<(std::ostream &out, BoundingBox bb);
};

#endif

