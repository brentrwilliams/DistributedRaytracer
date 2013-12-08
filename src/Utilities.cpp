/**
 * Utilities.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Utilities.hpp"

float fclamp(float min, float max, float val) 
{
   if (val < min)
      return min;
   else if (val > max) 
      return max;
   return val;
}

bool fEqual(float valA, float valB, float tolerance)
{
   return fabs(valA - valB) < tolerance;
}

bool vec3Equal(glm::vec3 val1, glm::vec3 val2, float tolerance)
{
   bool xEqual, yEqual, zEqual;
   
   xEqual = fEqual(val1.x, val2.x, tolerance);
   yEqual = fEqual(val1.y, val2.y, tolerance);
   zEqual = fEqual(val1.z, val2.z, tolerance);
   
   return  xEqual && yEqual && zEqual;
}
