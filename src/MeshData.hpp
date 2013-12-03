/**
 * MeshData.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef MeshData_HPP
#define MeshData_HPP

#include <vector>
#include <string>
#include <ostream>

#include "BoundingBox.hpp"
#include "Triangle.hpp"

#define VERTS_PER_TRI 9
#define UV_COORDS_PER_TRI 6

class MeshData
{
   public:
      std::vector<float>* triangleVertices;
      std::vector<float>* textureCoordinates;
      std::string* name;
      std::string* material;
      BoundingBox boundingBox;
      
      MeshData();
      MeshData(std::vector<float>* triangleVertices, std::vector<float>* textureCoordinates, std::string* name, std::string* material);
      ~MeshData();
      void calculateBoundingBox();
      friend std::ostream &operator<<(std::ostream &out, MeshData MeshData);
      
};

#endif
