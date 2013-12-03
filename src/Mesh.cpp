/**
 * Mesh.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Mesh.hpp"

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<float>* triangleVertices, std::vector<float>* textureCoordinates, char* name, char* material)
{
   this->name = name;
   this->material = material;
   verticesAndTexCoordsToTriangles(triangleVertices, textureCoordinates);
   calculateBoundingBox();
}

Mesh::Mesh(MeshData meshData)
{
   this->name = *meshData.name;
   this->material = *meshData.material;
   verticesAndTexCoordsToTriangles(meshData.triangleVertices, meshData.textureCoordinates);
   calculateBoundingBox();
}

Mesh::~Mesh()
{
}

std::ostream &operator<<(std::ostream &out, Mesh mesh)
{
   int i;
   out << "Mesh: " << mesh.name << "\n";
   out << "\tMaterial: " << mesh.material << "\n";
   out << "Bounding Box:\n\t" << mesh.boundingBox << "\n"; 
      
   out << "\nTriangles(" << mesh.triangles.size() << "): \n";
   for(i = 0; i < mesh.triangles.size(); i++)
      out << mesh.triangles[i] << "\n";

   return out;
}

void Mesh::calculateBoundingBox()
{
   int i;
   boundingBox.maxs = triangles[0].boundingBox.maxs;
   boundingBox.mins = triangles[0].boundingBox.mins;
   
   for (i = 1; i < triangles.size(); i++)
   {
      glm::vec3 currMaxs = triangles[i].boundingBox.maxs;
      glm::vec3 currMins = triangles[i].boundingBox.mins;
      if (currMaxs.x > boundingBox.maxs.x)
         boundingBox.maxs.x = currMaxs.x;
      if (currMins.x < boundingBox.mins.x)
         boundingBox.mins.x = currMins.x;
      
      if (currMaxs.y > boundingBox.maxs.y)
         boundingBox.maxs.y = currMaxs.y;
      if (currMins.y < boundingBox.mins.y)
         boundingBox.mins.y = currMins.y;
      
      if (currMaxs.z > boundingBox.maxs.z)
         boundingBox.maxs.z = currMaxs.z;
      if (currMins.z < boundingBox.mins.z)
         boundingBox.mins.z = currMins.z;
   }
}

void Mesh::verticesAndTexCoordsToTriangles(std::vector<float>* triangleVertices, std::vector<float>* textureCoordinates)
{
   int i;
   int numTriangles = triangleVertices->size() / VERTS_PER_TRI;
   
   for (i = 0; i < numTriangles; i++)
   {
      glm::vec3 v1(triangleVertices->at((i*VERTS_PER_TRI)), triangleVertices->at((i*VERTS_PER_TRI)+1), triangleVertices->at((i*VERTS_PER_TRI)+2));
      glm::vec3 v2(triangleVertices->at((i*VERTS_PER_TRI)+3), triangleVertices->at((i*VERTS_PER_TRI)+4), triangleVertices->at((i*VERTS_PER_TRI)+5));
      glm::vec3 v3(triangleVertices->at((i*VERTS_PER_TRI)+6), triangleVertices->at((i*VERTS_PER_TRI)+7), triangleVertices->at((i*VERTS_PER_TRI)+8)); 
      
      glm::vec2 uv1(textureCoordinates->at((i*UV_COORDS_PER_TRI)), textureCoordinates->at((i*UV_COORDS_PER_TRI)+1));
      glm::vec2 uv2(textureCoordinates->at((i*UV_COORDS_PER_TRI)+2), textureCoordinates->at((i*UV_COORDS_PER_TRI)+3));
      glm::vec2 uv3(textureCoordinates->at((i*UV_COORDS_PER_TRI)+4), textureCoordinates->at((i*UV_COORDS_PER_TRI)+5));
      
      Triangle triangle(v1, v2, v3, uv1, uv2, uv3);
      triangles.push_back(triangle);
   }
}
