/**
 * MeshData.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "MeshData.hpp"

MeshData::MeshData()
{
   triangleVertices = new std::vector<float>();
   textureCoordinates = new std::vector<float>();
   name = new std::string();
   material = new std::string();
}

MeshData::MeshData(std::vector<float>* triangleVertices, std::vector<float>* textureCoordinates, std::string* name, std::string* material)
{
   this->triangleVertices = triangleVertices;
   this->textureCoordinates = textureCoordinates;
   this->name = name;
   this->material = material;
}

MeshData::~MeshData()
{
   delete triangleVertices;
   delete textureCoordinates;
   delete name;
   delete material;
}

std::ostream &operator<<(std::ostream &out, MeshData MeshData)
{
   int i;
   out << "MeshData: " << *MeshData.name << "\n";
   if (!MeshData.material->empty())
      out << "\tMaterial: " << *MeshData.material << "\n";
      
   out << "\tVertices(" << MeshData.triangleVertices->size() << "): \n";
   for(i = 0; i < MeshData.triangleVertices->size(); i+=3)
      out << "\t\t(" << MeshData.triangleVertices->at(i) << ", " << MeshData.triangleVertices->at(i+1) << ", " << MeshData.triangleVertices->at(i+2) << ")\n";
   
   out << "\tTexture Coordinates: \n";
   for(i = 0; i < MeshData.textureCoordinates->size(); i+=3)
      out << "\t\t(" << MeshData.textureCoordinates->at(i) << ", " << MeshData.textureCoordinates->at(i+1) << ")\n";

   return out;
}

void MeshData::calculateBoundingBox()
{
   int i;
   glm::vec3 first((*triangleVertices)[0], (*triangleVertices)[1], (*triangleVertices)[2]);
   
   boundingBox.maxs = first;
   boundingBox.mins = first;
   
   for (i = 3; i < triangleVertices->size(); i+=3)
   {
      glm::vec3 current((*triangleVertices)[i], (*triangleVertices)[i+1], (*triangleVertices)[i+2]);
      if (current.x > boundingBox.maxs.x)
         boundingBox.maxs.x = current.x;
      if (current.x < boundingBox.mins.x)
         boundingBox.mins.x = current.x;
      
      if (current.y > boundingBox.maxs.y)
         boundingBox.maxs.y = current.y;
      if (current.y < boundingBox.mins.y)
         boundingBox.mins.y = current.y;
      
      if (current.z > boundingBox.maxs.z)
         boundingBox.maxs.z = current.z;
      if (current.z < boundingBox.mins.z)
         boundingBox.mins.z = current.z;
   }
}
