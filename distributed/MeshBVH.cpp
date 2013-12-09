/**
 * MeshBVH.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 
 
#include "MeshBVH.hpp"

MeshBVH::MeshBVH(std::vector<Triangle> triangles)
{
   root = new MeshBVHNode(triangles, X_AXIS);
}

bool MeshBVH::intersect(Ray ray, float *t, Triangle* triangleHit)
{
   return root->intersect(ray, t, triangleHit);
}
