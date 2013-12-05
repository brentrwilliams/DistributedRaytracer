/**
 * MTLReader.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "MTLReader.hpp"

MTLReader::MTLReader(const char* fileName)
{
   this->fileName = fileName;
   mtlFile.open(fileName, std::ifstream::in);
   if (!mtlFile.good())
   {
      std::cerr << "Unable to open file " << fileName << "\n";
      exit (EXIT_FAILURE);
   }
   read();
   mtlFile.close();
}

void MTLReader::read()
{
   int bufferSize = 512;
   char fileBuffer[bufferSize];
   char charBuffer[bufferSize];
   char* word;
   std::string stringBuffer;
   Material* currMaterial = NULL;

   while(mtlFile.good())
   {
      mtlFile.getline(fileBuffer, bufferSize);
      stringBuffer = fileBuffer;
      strcpy(charBuffer, stringBuffer.c_str());
      word = strtok(charBuffer, " \t");
    
      if (word != NULL && strcmp(word, "newmtl") == 0)
      {
         if (currMaterial != NULL)
            materials[currMaterial->name] = *currMaterial;
         currMaterial = new Material();
         word = strtok(NULL, " \t");
         
         if (word != NULL && strlen(word) > 1)
            currMaterial->name = word;
      }
      else if (word != NULL && strcmp(word, "illum") == 0)
      {
         word = strtok(NULL, " \t");
         if (word != NULL && strlen(word) > 0)
            currMaterial->illum = atoi(word);
      }
      else if (word != NULL && strcmp(word, "Ns") == 0)
      {
         word = strtok(NULL, " \t");
         if (word != NULL && strlen(word) > 0)
            currMaterial->ns = atof(word);
      }
      else if (word != NULL && strcmp(word, "Ka") == 0)
      {
         float vals[] = {0.0f, 0.0f, 0.0f};
         int count = 0;
         word = strtok(NULL, " \t");
         
         while (word != NULL && strlen(word) > 1 && count < 3)
         {
            vals[count] = atof(word);
            word = strtok(NULL, " \t");
            count++;
         }
         glm::vec3 ka(vals[0],vals[1],vals[2]);
         currMaterial->ka = ka;
      }
      else if (word != NULL && strcmp(word, "Kd") == 0)
      {
         float vals[] = {0.0f, 0.0f, 0.0f};
         int count = 0;
         word = strtok(NULL, " \t");
         
         while (word != NULL && strlen(word) > 1 && count < 3)
         {
            vals[count] = atof(word);
            word = strtok(NULL, " \t");
            count++;
         }
         glm::vec3 kd(vals[0],vals[1],vals[2]);
         currMaterial->kd = kd;
      }
      else if (word != NULL && strcmp(word, "Ks") == 0)
      {
         float vals[] = {0.0f, 0.0f, 0.0f};
         int count = 0;
         word = strtok(NULL, " \t");
         
         while (word != NULL && strlen(word) > 1 && count < 3)
         {
            vals[count] = atof(word);
            word = strtok(NULL, " \t");
            count++;
         }
         glm::vec3 ks(vals[0],vals[1],vals[2]);
         currMaterial->ks = ks;
      }
      else if (word != NULL && strcmp(word, "Ke") == 0)
      {
         float vals[] = {0.0f, 0.0f, 0.0f};
         int count = 0;
         word = strtok(NULL, " \t");
         
         while (word != NULL && strlen(word) > 1 && count < 3)
         {
            vals[count] = atof(word);
            word = strtok(NULL, " \t");
            count++;
         }
         glm::vec3 ke(vals[0],vals[1],vals[2]);
         currMaterial->ke = ke;
      }
   }
   
   if (currMaterial != NULL)
      materials[currMaterial->name] = *currMaterial;
}

std::map<std::string, Material> MTLReader::getMaterials()
{
   return materials;
}
