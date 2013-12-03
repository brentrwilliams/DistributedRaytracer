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
#include "Triangle.hpp"
#include "MeshData.hpp"

#define VERTS_PER_TRI 9
#define UV_COORDS_PER_TRI 6

class Mesh
{
   public:
      std::string name;
      std::string material;
      std::vector<Triangle> triangles;
      BoundingBox boundingBox;
      
      Mesh();
      Mesh(std::vector<float>* triangleVertices, std::vector<float>* textureCoordinates, char* name, char* material);
      Mesh(MeshData meshData);
      ~Mesh();
      void calculateBoundingBox();
      void verticesAndTexCoordsToTriangles(std::vector<float>* triangleVertices, std::vector<float>* textureCoordinates);
      
   private:
      friend std::ostream &operator<<(std::ostream &out, Mesh mesh);
      
};

#endif
