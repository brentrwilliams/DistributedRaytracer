/**
 * OBJReader.cpp
 *
 * @author Brent Williams brent.robert.williams@gmail.com
 */

#include "OBJReader.hpp"

OBJReader::OBJReader(char* objFileName)
{
   this->objFileName = objFileName;
   
   objFile.open(objFileName, std::ifstream::in);
   if (!objFile.good())
   {
      std::cerr << "Unable to open file " << objFileName << "\n";
      exit (EXIT_FAILURE);
   }
   
   sceneBoundingBox = getSceneBoundingBox();
   mtlFileName = getMtlFileName();
}

OBJReader::~OBJReader()
{
   objFile.close();
}

Mesh OBJReader::getMesh()
{
   char fileBuffer[BUFFER_SIZE];
   char charBuffer[BUFFER_SIZE];
   char* word;
   bool found = false;
   std::string stringBuffer;
   Mesh mesh;
   std::vector<float> vertices;
   std::vector<Face> faces;
   
   objFile.seekg(0, objFile.beg);
   objFile.clear();
   
   //Get to the first vertex line and process it
   while(objFile.good() && !found)
   {
      objFile.getline(fileBuffer, BUFFER_SIZE);
      stringBuffer = fileBuffer;
      strcpy(charBuffer, stringBuffer.c_str());
      word = strtok(charBuffer, " \t");
      
      if (word != NULL && strcmp(word, "v"))
      {
         found = true;
         
         word = strtok(NULL, " \t");
         while (word != NULL)
         {
            vertices.push_back(atof(word));
         }
      }
   }
   
   found = false;
   //Get all the vertices, the group name, the material and the first face
   while(objFile.good() && !found)
   {
      objFile.getline(fileBuffer, BUFFER_SIZE);
      stringBuffer = fileBuffer;
      strcpy(charBuffer, stringBuffer.c_str());
      word = strtok(charBuffer, " \t");
      
      if (word != NULL && strcmp(word, "v"))
      {
         word = strtok(NULL, " \t");
         while (word != NULL)
         {
            vertices.push_back(atof(word));
         }
      }
      
      if (word != NULL && strcmp(word, "g"))
      {
         word = strtok(NULL, " \t");
         if (word != NULL)
            mesh.name = word;
         else
            mesh.name = "";
      }
      
      if (word != NULL && strcmp(word, "usemtl"))
      {
         word = strtok(NULL, " \t");
         if (word != NULL)
            mesh.material = word;
         else
            mesh.material = "";
      }
      
      if (word != NULL && strcmp(word, "f"))
      {
         found = true;
         Face face;
         face.numVertices = 0;
         
         word = strtok(NULL, " \t");
         while (word != NULL)
         {
            face.vertexNumbers[face.numVertices] = atoi(word);
            face.numVertices++;
         }
         
         faces.push_back(face);
      }
   }
   
   
   
   return mesh;
}

BoundingBox OBJReader::getSceneBoundingBox()
{
   std::string stringBuffer;
   char fileBuffer[BUFFER_SIZE];
   bool foundFirst = false;
   float minX, minY, minZ, maxX, maxY, maxZ, x, y, z; 

   //Fill the start values
   while(objFile.good() && !foundFirst)
   {
      objFile.getline(fileBuffer, BUFFER_SIZE);
      stringBuffer = fileBuffer;
      stringBuffer = trim(stringBuffer);
      if (stringBuffer[0] == 'v' && stringBuffer[1] != 't')
      {
         stringBuffer = stringBuffer.substr(1);
         std::stringstream ss(stringBuffer);
         ss >> maxX >> maxY >> maxZ;
         
         minX = maxX;
         minY = maxY; 
         minZ = maxZ;
         foundFirst = true;
      }
   }
   
   while(objFile.good())
   {
      objFile.getline(fileBuffer, BUFFER_SIZE);
      stringBuffer = fileBuffer;
      stringBuffer = trim(stringBuffer);
      if (stringBuffer[0] == 'v' && stringBuffer[1] != 't')
      {
         stringBuffer = stringBuffer.substr(1);
         std::stringstream ss(stringBuffer);
         ss >> x >> y >> z;
         
         if (x > maxX)
            maxX = x;
         if (x < minX)
            minX = x;
            
         if (y > maxY)
            maxY = y;
         if (y < minY)
            minY = y;
         
         if (z > maxZ)
            maxZ = z;
         if (z < minZ)
            minZ = z;
      }
   }

   //Put the file stream back to the start and clear the state
   objFile.seekg(0, objFile.beg);
   objFile.clear();
   
   glm::vec3 mins(minX, minY, minZ);
   glm::vec3 maxs(maxX, maxY, maxZ);
   BoundingBox boundingBox(mins, maxs);
   
   return boundingBox;
}

std::string OBJReader::getMtlFileName()
{
   std::string mtl = "mtllib";
   std::string stringBuffer;
   std::string whitespace = " \t";
   char fileBuffer[BUFFER_SIZE];
   std::string fileName;
   size_t mtlEnd;
   bool found = false;
   
   objFile.seekg(0, objFile.beg);
   objFile.clear();
   
   while(objFile.good() && !found)
   {
      objFile.getline(fileBuffer, BUFFER_SIZE);
      stringBuffer = fileBuffer;
      stringBuffer = trim(stringBuffer);
      mtlEnd = stringBuffer.find_first_of(whitespace);

      if (stringBuffer.compare(0, mtlEnd, mtl) == 0)
      {
         found = true;
         fileName = stringBuffer.substr(mtlEnd);
         fileName = trim(fileName);
      }
   }
   
   //Put the file stream back to the start and clear the state
   objFile.seekg(0, objFile.beg);
   objFile.clear();
   
   return fileName;
}

//Get rid of leading and trailing whitespace
std::string OBJReader::trim(const std::string& str)
{
   std::string whitespace = " \t";
   std::string newStr = str;
   size_t start = newStr.find_first_not_of(whitespace);
   size_t end = newStr.find_last_not_of(whitespace);
   
   if (start == std::string::npos)
        return ""; // no content
   
   return str.substr(start, end-start+1);
}
