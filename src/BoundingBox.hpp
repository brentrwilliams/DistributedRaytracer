/**
 * BoundingBox.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

#include <ostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class BoundingBox
{
   public:
      glm::vec3 mins;
      glm::vec3 maxs;
      
      BoundingBox();
      BoundingBox(glm::vec3 mins, glm::vec3 maxs);
      friend std::ostream &operator<<(std::ostream &out, BoundingBox bb);
};

#endif
