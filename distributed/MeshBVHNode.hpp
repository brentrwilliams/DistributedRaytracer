/**
 * MeshBVHNode.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef MESH_BVH_NODE_HPP
#define MESH_BVH_NODE_HPP

#include <vector>
#include <algorithm>

#include "BoundingBox.hpp"
#include "Triangle.hpp"
#include "Ray.hpp"

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

class MeshBVHNode
{
   public:
      MeshBVHNode* left;
      MeshBVHNode* right;
      BoundingBox boundingBox;
      Triangle triangle;
      
      MeshBVHNode(std::vector<Triangle> triangles, int axis);
      bool intersect(Ray ray, float *t, Triangle* triangleHit);
};

#endif

