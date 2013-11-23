/**
 * OBJReader.hpp
 *
 * @author Brent Williams brent.robert.williams@gmail.com
 */

#ifndef OBJ_READER_HPP
#define OBJ_READER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <cstddef>

#include "Mesh.hpp"
#include "BoundingBox.hpp"

#define BUFFER_SIZE

class OBJReader
{
   public:
      char *fileName;
      
      OBJReader(char* fileName);
      ~OBJReader();
      Mesh getMesh();
      
   private:
      std::ifstream file;
      
      BoundingBox getSceneBoundingBox();
      
}

#endif
