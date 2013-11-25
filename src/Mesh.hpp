/**
 * Mesh.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <string>

#include "Face.hpp"

class Mesh
{
   public:
      std::vector<float> triangleVertices;
      std::string name;
      std::string material;
      
   private:
      
      
};

#endif
