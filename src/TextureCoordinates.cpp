/**
 * TextureCoordinates.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "TextureCoordinates.hpp"

std::ostream &operator<<(std::ostream &out, TextureCoordinates texCoords)
{
   if (texCoords.numCoordinates == 3)
      out << "<" << texCoords.coordinates[0] << ", " << texCoords.coordinates[1] << ", " << texCoords.coordinates[2] << ">";
   else
      out << "<" << texCoords.coordinates[0] << ", " << texCoords.coordinates[1] << ", " << texCoords.coordinates[2] << ", " << texCoords.coordinates[3]<< ">";
   return out;
}
