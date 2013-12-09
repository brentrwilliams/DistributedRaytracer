/**
 * Camera.hpp
 *
 * @author Brent Williams brent.robert.williams@gmail.com
 *
 */

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>
#include <string.h>

#define MAX_CHARS_PER_LINE 512

class Camera
{
   public:
      Camera(char* fileName);
      friend std::ostream& operator<<(std::ostream& os, const Camera& camera);
      void read(std::ifstream &inFile);

      glm::vec3 location;
      glm::vec3 up; 
      glm::vec3 right;
      glm::vec3 lookAt;
};

#endif
