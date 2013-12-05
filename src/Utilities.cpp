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
