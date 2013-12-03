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
#include <string.h>
#include <cstddef>
#include <sstream>
#include <vector>

#include "Mesh.hpp"
#include "BoundingBox.hpp"
#include "Face.hpp"

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
      bool hasNextMesh();
      Mesh* getMesh();
      
   private:
      std::ifstream objFile;
      
      void facesVerticesTexCoordsToTriangles(std::vector<float> vertices, 
       std::vector<Face> faces, std::vector<float> textureCoordinates, 
       Mesh* meshPtr);
      BoundingBox getSceneBoundingBox();
      std::string getMtlFileName();
      std::string trim(const std::string& str);
      
};

#endif
