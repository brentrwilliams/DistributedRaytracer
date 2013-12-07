/**
 * MeshBVHNode.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "MeshBVHNode.hpp"

MeshBVHNode::MeshBVHNode(std::vector<Triangle> triangles, int axis)
{
   int numTris = triangles.size();
   
   if (numTris == 1)
   {
      left = NULL;
      right = NULL;
      boundingBox = triangles[0].boundingBox;
      triangle = triangles[0];
   }
   else
   {
      int nextAxis;
      
      if (axis == X_AXIS)
      {
         sort(triangles.begin(), triangles.end(), xAxisSort);
         nextAxis = Y_AXIS;
      }
      else if (axis == Y_AXIS)
      {
         sort(triangles.begin(), triangles.end(), yAxisSort);
         nextAxis = Z_AXIS;
      }
      else
      {
         sort(triangles.begin(), triangles.end(), zAxisSort);
         nextAxis = X_AXIS;
      }
      
      // Split vector into 2 parts
      int half = triangles.size() / 2;
      std::vector<Triangle> leftTris(triangles.begin(), triangles.begin() + half);
      std::vector<Triangle> rightTris(triangles.begin() + half, triangles.end());
      
      left = new MeshBVHNode(leftTris, nextAxis);
      right = new MeshBVHNode(rightTris, nextAxis);
      BoundingBox* boundingBoxPtr = new BoundingBox(left->boundingBox, right->boundingBox);
      boundingBox = *boundingBoxPtr;
      //triangle = NULL;
   }
}

bool MeshBVHNode::intersect(Ray ray, float *t, Triangle* triangleHit)
{
   bool leftBool, rightBool, leafBool;
   float lt, rt;
   Triangle lTri, rTri;

   if (boundingBox.intersect(ray))
   {
      if (!(left == NULL && right == NULL)) //It is NOT a leaf node
      {
         if (left == NULL)
            printf("NULL LEFT!\n");
         if (left == NULL)
            printf("NULL RIGHT!\n");
         leftBool = left->intersect(ray, &lt, &lTri);
         rightBool = right->intersect(ray, &rt, &rTri);
         
         if (leftBool && rightBool)
         {
            if (lt < rt)
            {
               *t = lt;
               *triangleHit = lTri;
            }
            else
            {
               *t = rt;
               *triangleHit = rTri;
            }
            //cout << "\t" << *triangleHit << endl;
            return true;
         }
         else if (leftBool)
         {
            *t = lt;
            *triangleHit = lTri;
            //cout << "\t" << *triangleHit << endl;
            return true;
         }
         else if (rightBool)
         {
            *t = rt;
            *triangleHit = rTri;
            //cout << "\t" << *triangleHit << endl;
            return true;
         }
         else
            return false;
         
      }
      else //It is a leaf node
      {
         *triangleHit = triangle;
         leafBool = triangle.intersect(ray, t);
         //std::cout << "Leaf: " << leafBool << "\n";
         //std::cout << triangle << "\n";
         
         //if (leafBool)
         //   std::cout << "HIT!\n";
         return leafBool;
      }
   }
   else
      return false;
   
   return false;
}























