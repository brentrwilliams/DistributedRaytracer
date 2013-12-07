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
   bvh = new MeshBVH(triangles);
}

Mesh::Mesh(MeshData meshData)
{
   this->name = *meshData.name;
   this->material = *meshData.material;
   verticesAndTexCoordsToTriangles(meshData.triangleVertices, meshData.textureCoordinates);
   calculateBoundingBox();
   bvh = new MeshBVH(triangles);
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
      
      glm::vec2 uv1(0.0f,0.0f);
      glm::vec2 uv2(0.0f,0.0f);
      glm::vec2 uv3(0.0f,0.0f);
      if (textureCoordinates->size() > 0)
      {
         uv1.x = textureCoordinates->at((i*UV_COORDS_PER_TRI));
         uv1.y = textureCoordinates->at((i*UV_COORDS_PER_TRI)+1);
         
         uv2.x = textureCoordinates->at((i*UV_COORDS_PER_TRI)+2);
         uv2.x = textureCoordinates->at((i*UV_COORDS_PER_TRI)+3);
         
         uv3.x = textureCoordinates->at((i*UV_COORDS_PER_TRI)+4);
         uv3.y = textureCoordinates->at((i*UV_COORDS_PER_TRI)+5);
      }
      
      Triangle triangle(v1, v2, v3, uv1, uv2, uv3);
      triangle.calculateBoundingBox();
      triangles.push_back(triangle);
   }
}

std::vector<glm::vec3> Mesh::getEmissiveSamples()
{
   std::vector<glm::vec3> samples;
   int i;
   unsigned int seed = 1;
   
   srand(seed);
   
   for (i = 0; i < NUM_LIGHT_SAMPLES; i++)
   {
      //Get a random triangles from the mesh
      int triIndex = rand() % triangles.size();
      Triangle triangle = triangles[triIndex];
      
      //Get a random point within the triangle
      float r1 = (rand()%100) / 100.0f;
      float r2 = (rand()%100) / 100.0f;
      glm::vec3 samplePoint = (triangle.v1 * ((float)(1 - sqrt(r1)))) + (triangle.v2 * ((float)(sqrt(r1) * (1 - r2)))) + (triangle.v3 * ((float)((sqrt(r1) * r2))));
      samples.push_back(samplePoint);
   }

   return samples;
}

bool Mesh::intersect(Ray ray, float *t, Triangle* triangleHit)
{
   return bvh->intersect(ray, t, triangleHit);
}
