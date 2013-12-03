/**
 * BoundingBox.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "BoundingBox.hpp"

BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(glm::vec3 mins, glm::vec3 maxs)
{
   this->mins = mins;
   this->maxs = maxs;
   calculateCorners();
   calculateCenter();
}

BoundingBox::BoundingBox(BoundingBox bb1, BoundingBox bb2)
{
   mins.x = bb1.mins.x;
   mins.y = bb1.mins.y;
   mins.z = bb1.mins.z;
   
   maxs.x = bb1.maxs.x;
   maxs.y = bb1.maxs.y;
   maxs.z = bb1.maxs.z;
   
   if (bb2.mins.x < mins.x)
      mins.x = bb2.mins.x;
   if (bb2.mins.y < mins.y)
      mins.y = bb2.mins.y;
   if (bb2.mins.z < mins.z)
      mins.z = bb2.mins.z;
   
   if (bb2.maxs.x > maxs.x)
      maxs.x = bb2.maxs.x;
   if (bb2.maxs.y > maxs.y)
      maxs.y = bb2.maxs.y;
   if (bb2.maxs.z > maxs.z)
      maxs.z = bb2.maxs.z;
   
   calculateCorners();
   calculateCenter();
}

void BoundingBox::calculateCorners()
{
   int i, j, k, index;
   
   for (i = 0; i < 2; i++)
   {
      for (j = 0; j < 2; j++)
      {
         for (k = 0; k < 2; k++)
         {
            index = (4 * i) + (2 * j) + k;
            if (i)
               corner[index].x = maxs.x;
            else
               corner[index].x = mins.x;
            
            if (j)
               corner[index].y = maxs.y;
            else
               corner[index].y = mins.y;
            
            if (k)
               corner[index].z = maxs.z;
            else
               corner[index].z = mins.z;
         }
      }
   }
}

bool BoundingBox::intersect(Ray ray)
{
   float tMin, tMax, tyMin, tyMax, tzMin, tzMax, divX, divY, divZ;
   float eMin = 0, eMax = 1000000;
   
   divX = 1 / ray.d.x;
   if (divX >= 0)
   {
      tMin = (mins.x - ray.p.x) * divX;
      tMax = (maxs.x - ray.p.x) * divX;
   }
   else
   {
      tMin = (maxs.x - ray.p.x) * divX;
      tMax = (mins.x - ray.p.x) * divX;
   }
   
   divY = 1 / ray.d.y;
   if (divY >= 0)
   {
      tyMin = (mins.y - ray.p.y) * divY;
      tyMax = (maxs.y - ray.p.y) * divY;
   }
   else
   {
      tyMin = (maxs.y - ray.p.y) * divY;
      tyMax = (mins.y - ray.p.y) * divY;
   }
   
   if ( (tMin > tyMax) || (tyMin  > tMax) )
      return false;
   
   if (tyMin > tMin)
      tMin = tyMin;
   if (tyMax < tMax)
      tMax = tyMax;
   
   divZ = 1 / ray.d.z;
   if (divZ >= 0)
   {
      tzMin = (mins.z - ray.p.z) * divZ;
      tzMax = (maxs.z - ray.p.z) * divZ;
   }
   else
   {
      tzMin = (maxs.z - ray.p.z) * divZ;
      tzMax = (mins.z - ray.p.z) * divZ;
   }
   
   if ( (tMin > tzMax) || (tzMin  > tMax) )
      return false;
   
   if (tzMin > tMin)
      tMin = tzMin;
   if (tzMax < tMax)
      tMax = tzMax;
   
   if (tMin > eMin && tMin < eMax)
      return true;
   
   if (tMax > eMin && tMax < eMax)
      return true;
   
   return false;
}


void BoundingBox::transform(glm::mat4 trans)
{
   int i;
   
   mins.x = MAXIMUM_FLOAT;
   mins.y = MAXIMUM_FLOAT;
   mins.z = MAXIMUM_FLOAT;
   
   maxs.x = MINIMUM_FLOAT;
   maxs.y = MINIMUM_FLOAT;
   maxs.z = MINIMUM_FLOAT;
   //myprintglm::mat4(trans);
   
   for (i = 0; i < 8; i++)
   {
      glm::vec4 tempCorner1(corner[i].x, corner[i].y, corner[i].z, 1);
      glm::vec4 tempCorner = trans * tempCorner1;
      
      corner[i].x = tempCorner.x;
      corner[i].y = tempCorner.y;
      corner[i].z = tempCorner.z;
      //printf("Tranformed corner[%d]: <%f, %f, %f>\n", i, tempCorner.x, tempCorner.y, tempCorner.z); 
      
      if (corner[i].x < mins.x)
         mins.x = corner[i].x;
      if (corner[i].y < mins.y)
         mins.y = corner[i].y;
      if (corner[i].z < mins.z)
         mins.z = corner[i].z;
      
      if (corner[i].x > maxs.x)
         maxs.x = corner[i].x;
      if (corner[i].y > maxs.y)
         maxs.y = corner[i].y;
      if (corner[i].z > maxs.z)
         maxs.z = corner[i].z;
   }
   
   calculateCorners();
   calculateCenter();
}

void BoundingBox::calculateCenter()
{
   center = mins + maxs;
   center /= 2;
}

std::ostream &operator<<(std::ostream &out, BoundingBox bb)
{
   out << "(" << bb.mins.x << ", " << bb.mins.y << ", " << bb.mins.z << ") to ";
   out << "(" << bb.maxs.x << ", " << bb.maxs.y << ", " << bb.maxs.z << ")";
   return out;
}
