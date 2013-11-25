/**
 * TextureCoordinates.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef TEXTURE_COORDINATES_HPP
#define TEXTURE_COORDINATES_HPP

#include <ostream>

class TextureCoordinates
{
   public:
      int numCoordinates;
      float coordinates[4];
      friend std::ostream &operator<<(std::ostream &out, TextureCoordinates texCoords);
};

#endif
