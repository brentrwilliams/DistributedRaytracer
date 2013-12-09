/**
 * OBJReader.cpp
 *
 * @author Brent Williams brent.robert.williams@gmail.com
 *
 * This class only deals with a subset of the obj format. This includes:
 * - v 
 * - vt
 * - f (including tris, quads and negative face numbers but not "/'s")
 * - g 
 * - usemtl
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

bool OBJReader::hasNextMesh()
{
   return objFile.good();
}

//If there are more meshes, returns the next mesh
MeshData* OBJReader::getMeshData()
{
   char fileBuffer[BUFFER_SIZE];
   char charBuffer[BUFFER_SIZE];
   char* word;
   bool gHit = false;
   bool done = false;
   int faceNum;
   int texCount;
   std::string stringBuffer;
   MeshData *meshDataPtr = new MeshData();
   std::vector<float> vertices;
   std::vector<Face> faces;
   std::vector<float> textureCoordinates;
   
   std::cout << "In getMesh()\n";
   
   while(objFile.good() && !done)
   {
      objFile.getline(fileBuffer, BUFFER_SIZE);
      stringBuffer = fileBuffer;
      strcpy(charBuffer, stringBuffer.c_str());
      word = strtok(charBuffer, " \t");
      
      std::cout << "Processing line: " << fileBuffer << "\n";
      
      if (gHit && word != NULL && strcmp(word, "v") == 0)
      {
         //std::cout << "In done case\n";
         //std::cout << "Last line: " << fileBuffer << "\n";
         //reset the file ptr to before that line
         objFile.seekg(-1*(strlen(fileBuffer)+1), objFile.cur);
         //objFile.getline(fileBuffer, BUFFER_SIZE);
         //std::cout << "New last line: " << fileBuffer << "\n";
         //objFile.seekg(-1*(strlen(fileBuffer)+1), objFile.cur);
         done = true;
      }
      else if (word != NULL && strcmp(word, "v") == 0)
      {
         //std::cout << "In v\n";
         word = strtok(NULL, " \t");
         
         while (word != NULL && strlen(word) > 1)
         {
           // std::cout << "\tword: " << word << " with length: " << strlen(word) << "\n";
            vertices.push_back(atof(word));
            word = strtok(NULL, " \t");
         }
      }
      else if (word != NULL && strcmp(word, "vt") == 0)
      {
         //std::cout << "In vt\n";
         texCount = 0;
         word = strtok(NULL, " \t");
         while (word != NULL && strlen(word) > 1 && texCount < 2)
         {
            textureCoordinates.push_back(atof(word));
            word = strtok(NULL, " \t");
            texCount++;
         }
      }
      else if (word != NULL && strcmp(word, "f") == 0)
      {
         Face face;
         face.numVertices = 0;
         
         std::cout << "In f\n";
         
         word = strtok(NULL, " \t");
         while (word != NULL && strlen(word) > 0)
         {
            faceNum = atoi(word);
            std::cout << "\tword: " << word << " with val: " << faceNum << "\n";
            if (faceNum >= 0)
            {
               face.vertexNumbers[face.numVertices] = faceNum;
               face.numVertices++;
            }
            else //Deal with negative face numbers as in spec
            {
               face.vertexNumbers[face.numVertices] = ((vertices.size()/3) + faceNum + 1);
               face.numVertices++;
            }
            word = strtok(NULL, " \t");
         }
         
         faces.push_back(face);
         std::cout << faces.size() << "\n";
      }
      else if (word != NULL && strcmp(word, "g") == 0)
      {
         gHit = true;
         word = strtok(NULL, " \t");
         if (word != NULL)
            meshDataPtr->name->assign(word);
         else
            meshDataPtr->name->assign("");
         //std::cout << "In g: " << mesh.name << "\n";
      }
      else if (word != NULL && strcmp(word, "usemtl") == 0)
      {
         //std::cout << "In usemtl\n";
         word = strtok(NULL, " \t");
         if (word != NULL)
            meshDataPtr->material->assign(word);
         else
            meshDataPtr->material->assign("");
      }
      
   }
   
   std::cout << "before: faces.size(): " << faces.size() << "\n";
   
   facesVerticesTexCoordsToTriangles(vertices, faces, textureCoordinates, meshDataPtr);
   
   return meshDataPtr;
}

void OBJReader::facesVerticesTexCoordsToTriangles(std::vector<float> vertices, 
 std::vector<Face> faces, std::vector<float> textureCoordinates, MeshData* meshDataPtr)
{
   int i, j;
   
   std::cout << "after: faces.size(): " << faces.size() << "\n";
   
   for (i = 0; i < faces.size(); i++)
   {
      if (faces[i].numVertices == 3)
      {
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[0]-1)*3]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[0]-1)*3+1]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[0]-1)*3+2]);
         
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[1]-1)*3]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[1]-1)*3+1]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[1]-1)*3+2]);
         
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[2]-1)*3]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[2]-1)*3+1]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[2]-1)*3+2]);

         if (textureCoordinates.size() > 0)
         {
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[0]-1)*2]);
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[0]-1)*2+1]);
            
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[1]-1)*2]);
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[1]-1)*2+1]);
            
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[2]-1)*2]);
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[2]-1)*2+1]);
         }
      }
      else if (faces[i].numVertices == 4)
      {
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[0]-1)*3]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[0]-1)*3+1]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[0]-1)*3+2]);
         
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[1]-1)*3]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[1]-1)*3+1]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[1]-1)*3+2]);
         
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[2]-1)*3]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[2]-1)*3+1]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[2]-1)*3+2]);
         
         
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[0]-1)*3]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[0]-1)*3+1]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[0]-1)*3+2]);
         
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[2]-1)*3]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[2]-1)*3+1]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[2]-1)*3+2]);
         
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[3]-1)*3]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[3]-1)*3+1]);
         meshDataPtr->triangleVertices->push_back(vertices[(faces[i].vertexNumbers[3]-1)*3+2]);
         
         if (textureCoordinates.size() > 0)
         {
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[0]-1)*2]);
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[0]-1)*2+1]);
            
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[1]-1)*2]);
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[1]-1)*2+1]);
            
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[2]-1)*2]);
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[2]-1)*2+1]);
            
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[0]-1)*2]);
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[0]-1)*2+1]);
            
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[2]-1)*2]);
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[2]-1)*2+1]);
            
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[3]-1)*2]);
            meshDataPtr->textureCoordinates->push_back(textureCoordinates[(faces[i].vertexNumbers[3]-1)*2+1]);
         }
      }
      else
      {
         std::cerr << "Mesh " << *meshDataPtr->name << "'s face " << i << " has " << faces[i].numVertices;
         std::cerr << " vertices. Exitting...\n";
         exit(EXIT_FAILURE);
      }
      
   }
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
