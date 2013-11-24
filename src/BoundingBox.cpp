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
}

std::ostream &operator<<(std::ostream &out, BoundingBox bb)
{
   out << "(" << bb.mins.x << ", " << bb.mins.y << ", " << bb.mins.z << ") to ";
   out << "(" << bb.maxs.x << ", " << bb.maxs.y << ", " << bb.maxs.z << ")";
   return out;
}
