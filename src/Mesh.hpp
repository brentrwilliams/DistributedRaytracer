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

#include "BoundingBox.hpp"

class Mesh
{
   public:
      std::vector<float>* triangleVertices;
      std::vector<float>* textureCoordinates;
      std::string* name;
      std::string* material;
      BoundingBox boundingBox;
      
      Mesh();
      Mesh(std::vector<float>* triangleVertices, std::vector<float>* textureCoordinates, std::string* name, std::string* material);
      ~Mesh();
      void calculateBoundingBox();
      
   private:
      friend std::ostream &operator<<(std::ostream &out, Mesh mesh);
      
};

#endif
