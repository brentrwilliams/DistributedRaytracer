/**
 * OBJReader.cpp
 *
 * @author Brent Williams brent.robert.williams@gmail.com
 */
 
OBJReader::OBJReader(const char* fileName)
{
   this.fileName = fileName;
   
   file.open(fileName, std::ifstream::in);
   if (!file.good())
   {
      std::cerr << "Unable to open file " + fileName << "\n";
      exit (EXIT_FAILURE);
   }
}

OBJReader::~OBJReader()
{
   file.close();
}

Mesh OBJReader::getMesh()
{
   Mesh mesh;
   return mesh;
}

BoundingBox OBJReader::getSceneBoundingBox()
{
   std::string stringBuffer;
   char fileBuffer[BUFFER_SIZE];
   bool foundFirst = false;
   float minX, minY, minZ, maxX, maxY, maxZ, x, y, z; 

   //Fill the start values
   while(file.good() && !foundFirst)
   {
      stringBuffer = file.getLine(buffer, BUFFER_SIZE);
      stringBuffer = trim(stringBuffer);
      if (stringBuffer[0] == 'v')
      {
         stringBuffer = stringBuffer.substring(1);
         std::stringstream ss(stringBuffer);
         ss >> maxX >> maxY >> maxZ;
         
         minX = maxX;
         minY = maxY; 
         minZ = maxZ;
         foundFirst = true;
      }
   }
   
   while(file.good())
   {
      stringBuffer = file.getLine(buffer, BUFFER_SIZE);
      stringBuffer = trim(stringBuffer);
      if (stringBuffer[0] == 'v')
      {
         stringBuffer = stringBuffer.substring(1);
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
   file.(0, file.beg);
   file.clear();
   
   vec3 mins(minX, minY, minZ);
   vec3 maxs(maxX, maxY, maxZ);
   BoundingBox boundingBox(mins, maxs);
   
   return boundingBox;
}

//Get rid of leading and trailing whitespace
std::string OBJReader::trim(const std::string& str)
{
   std::string& whitespace = " \t";
   std::string::iterator strBegin = str.find_first_not_of(whitespace);
   if (strBegin == std::string::npos)
      return "";

   std::string::iterator strEnd = str.find_last_not_of(whitespace);
   std::string::iterator strRange = strEnd - strBegin + 1;

   return str.substr(strBegin, strRange);
}
