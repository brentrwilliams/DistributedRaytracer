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
#include <stdlib.h>
#include <math.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "BoundingBox.hpp"
#include "Triangle.hpp"
#include "MeshData.hpp"
#include "MeshBVH.hpp"
#include "Ray.hpp"
#include "Utilities.hpp"

#define VERTS_PER_TRI 9
#define UV_COORDS_PER_TRI 6
#define NUM_LIGHT_SAMPLES 4

class Mesh
{
   public:
      std::string name;
      std::string material;
      std::vector<Triangle> triangles;
      BoundingBox boundingBox;
      MeshBVH* bvh;
      
      Mesh();
      Mesh(std::vector<float>* triangleVertices, std::vector<float>* textureCoordinates, char* name, char* material);
      Mesh(MeshData meshData);
      ~Mesh();
      void calculateBoundingBox();
      void calculateVertexNormals();
      void calculateFaceNormals();
      void verticesAndTexCoordsToTriangles(std::vector<float>* triangleVertices, std::vector<float>* textureCoordinates);
      std::vector<glm::vec3> getEmissiveSamples();
      bool intersect(Ray ray, float *t, Triangle* triangleHit);
      
   private:
      friend std::ostream &operator<<(std::ostream &out, Mesh mesh);
      
};

#endif
