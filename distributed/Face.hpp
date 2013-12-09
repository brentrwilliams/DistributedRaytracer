/**
 * Face.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef FACE_HPP
#define FACE_HPP

#include <ostream>

class Face
{
   public:
      int numVertices;
      int vertexNumbers[4];
      friend std::ostream &operator<<(std::ostream &out, Face face);
};

#endif
