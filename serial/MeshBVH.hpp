/**
 * MeshBVH.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef MESH_BVH_HPP
#define MESH_BVH_HPP

#include <vector>

#include "MeshBVHNode.hpp"
#include "Ray.hpp"

class MeshBVH
{
   public:
      MeshBVHNode* root;
   
      MeshBVH(std::vector<Triangle> triangles);
      bool intersect(Ray ray, float *t, Triangle* triangleHit);
};

#endif

