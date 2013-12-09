/**
 * Face.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Face.hpp"

std::ostream &operator<<(std::ostream &out, Face face)
{
   if (face.numVertices == 3)
      out << "<" << face.vertexNumbers[0] << ", " << face.vertexNumbers[1] << ", " << face.vertexNumbers[2] << ">";
   else
      out << "<" << face.vertexNumbers[0] << ", " << face.vertexNumbers[1] << ", " << face.vertexNumbers[2] << ", " << face.vertexNumbers[3]<< ">";
   return out;
}
