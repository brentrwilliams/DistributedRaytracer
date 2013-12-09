/**
 * Material.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <ostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Material
{
   public:
      Material();
      ~Material();
      bool isEmissive();
      
      std::string name;
      int illum;
      glm::vec3 ka;
      glm::vec3 kd;
      glm::vec3 ks;
      glm::vec3 ke;
      float ns;
      friend std::ostream &operator<<(std::ostream &out, Material material);
};

#endif

