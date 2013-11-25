/**
 * Mesh.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <string>
#include <ostream>

#include "Face.hpp"

class Mesh
{
   public:
      std::vector<float> triangleVertices;
      std::vector<float> textureCoordinates;
      std::string name;
      std::string material;
      
   private:
      friend std::ostream &operator<<(std::ostream &out, Mesh mesh);
      
};

#endif
