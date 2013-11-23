/**
 * BoundingBox.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

public class BoundingBox
{
   public:
      glm::vec3 mins;
      glm::vec3 maxs;
}

#endif
