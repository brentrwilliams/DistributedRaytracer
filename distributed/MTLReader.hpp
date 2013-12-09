/**
 * MTLReader.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef MTL_READER_HPP
#define MTL_READER_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <map>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Material.hpp"

class MTLReader
{
   public:
      std::string fileName;
      
      MTLReader(const char* fileName);
      std::map<std::string, Material> getMaterials();
      
   private:
      std::ifstream mtlFile;
   
      void read();
      std::map<std::string, Material> materials;
};

#endif
