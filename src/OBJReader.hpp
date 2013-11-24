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
#include <sstream>

#include "Mesh.hpp"
#include "BoundingBox.hpp"

#define BUFFER_SIZE 256
#define STRING_SIZE 256

class OBJReader
{
   public:
      std::string objFileName;
      std::string mtlFileName;
      BoundingBox sceneBoundingBox;
      
      OBJReader(char* objFileName);
      ~OBJReader();
      Mesh getMesh();
      
   private:
      std::ifstream objFile;
      
      BoundingBox getSceneBoundingBox();
      std::string getMtlFileName();
      std::string trim(const std::string& str);
      
};

#endif
