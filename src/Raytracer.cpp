/**
 * Raytracer.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Raytracer.hpp"

Raytracer::Raytracer(int imageWidth, int imageHeight, char* objFileName, char* cameraFileName)
{
   this->imageWidth = imageWidth;
   this->imageHeight = imageHeight; 
   objReader = new OBJReader(objFileName);
   camera = new Camera(cameraFileName);
   MTLReader mtlReader(objReader->mtlFileName.c_str());
   materials = mtlReader.getMaterials();
   
   image.allocateImage(imageWidth, imageHeight);
   zBuffer = (float **) malloc(imageWidth*sizeof(float*));
   int i;
   for (i = 0; i < imageWidth; i++)
      zBuffer[i] = (float *) malloc(imageHeight*sizeof(float));
      
   for( std::map<std::string, Material>::iterator matIt=materials.begin(); matIt!=materials.end(); ++matIt)
   {
       std::cout << (*matIt).second << endl;
   }
}

Raytracer::~Raytracer()
{
   delete objReader;
   delete camera;
}

void Raytracer::trace()
{
   int i, j;
   
   // Get all the meshes
   MeshData* tempMeshData;
   Mesh* tempMesh;
   
   while (objReader->hasNextMesh())
   {
      tempMeshData = objReader->getMeshData();
      Mesh tempMesh(*tempMeshData);
      std::cout << "\n" << tempMesh  << "\n";
      meshes.push_back(tempMesh);
   }
   
   vector<glm::vec3> samples = meshes[1].getEmissiveSamples();
   for (i = 0; i < samples.size(); i++)
   {
      std::cout << "<" << samples[i].x << ", " << samples[i].y << ", " << samples[i].z << ">\n"; 
   }
   
   std::cout << "Num meshes: " << meshes.size() << "\n";
   
   //Find all emissive meshes
   for (i = 0; i < meshes.size(); i++)
   {
      Material currMaterial = materials[meshes[i].material];
      if (currMaterial.isEmissive())
         emissiveMeshes.push_back(&meshes[i]);
   }
   std::cout << "Emissive meshes:\n";
   for (i = 0; i < emissiveMeshes.size(); i++)
   {
      std::cout << *emissiveMeshes[i] << "\n";
   }
   //Calculate rays
   
   Ray ray;
   RayCalcInfo rayCalcInfo;
   
   rayCalcInfo.l = -length(camera->right) / 2;
   rayCalcInfo.r = length(camera->right) / 2;
   rayCalcInfo.b = -length(camera->up) / 2;
   rayCalcInfo.t = length(camera->up) / 2;
   
   rayCalcInfo.u = camera->right / length(camera->right);
   rayCalcInfo.v = camera->up / length(camera->up);
   rayCalcInfo.w = cross(rayCalcInfo.u,rayCalcInfo.v);
   
   rayCalcInfo.imgWidth = image.width;
   rayCalcInfo.imgHeight = image.height;
   
   rayCalcInfo.p_0 = camera->location;
   
   vec3 color;
   int numPixels = image.width * image.height;
   int pixel = 1;
   int percent = 0;

   for (i = 0; i < image.width; i++)
   {
      for (j = 0; j < image.height; j++)
      {
         rayCalcInfo.i = i;
         rayCalcInfo.j = j;
         
         color = calculatePixelColor(rayCalcInfo, i, j);
         
         image.r[i][j] = color.x;
         image.g[i][j] = color.y;
         image.b[i][j] = color.z;
         
         
         //cerr << "Calculating pixel [" << i << "][" << j << "]\n";
         
         if ( ((pixel * 100) / numPixels) > percent)
         {
            percent++;
            cerr << percent << "%% complete\n";
         }
         pixel++;
      }
   }
}

glm::vec3 Raytracer::calculatePixelColor(RayCalcInfo rayCalcInfo, int i, int j)
{
   Ray ray;
   vec3 color(0,0,0);
   int x, y;
   float z = MAX_FLOAT;
   ray.calculateRay(rayCalcInfo, 1, 1); 
   color = traceRay(ray, &z);
   
   zBuffer[i][j] = z;
   return color;
}

void Raytracer::saveImage(char *imageName)
{
   image.writeTGA(imageName);
}

glm::vec3 Raytracer::traceRay(Ray &ray, float *zValue)
{
   bool intersected;
   float t = MAX_FLOAT;
   int meshIndex;
   Triangle triangleHit;
   vec3 color(0.0f, 0.0f, 0.0f);
   
   intersected = intersectGeometry(ray, &t, &triangleHit, &meshIndex);
   
   if (intersected && t < (*zValue)) 
   {
      color = calculateHitColor(ray, t, triangleHit, meshIndex);
   }
   
   return color;
}

bool Raytracer::intersectGeometry(Ray ray, float *t, Triangle* triangleHit, int* meshIndex)
{
   int i, j;
   float currT;
   Mesh currMesh;
   bool hit = false;
   for (i = 0; i < meshes.size(); i++)
   {
      currMesh = meshes[i];
      
      if (currMesh.boundingBox.intersect(ray))
      {
         for (j = 0; j < currMesh.triangles.size(); j++)
         {
            if(currMesh.triangles[j].intersect(ray, &currT))
            {
               hit = true;
               
               if (currT < (*t))
               {
                  *t = currT;
                  *triangleHit = currMesh.triangles[j];
                  *meshIndex = i;
               }
               
            }
         }
      }
   }
   return hit;
}

//Currently only doing illum 2
glm::vec3 Raytracer::calculateHitColor(Ray ray, float t, Triangle triangleHit, int meshIndex)
{
   glm::vec3 color(0.0f, 0.0f, 0.0f);
   float ia = 0.0;
   
   Material material = materials[meshes[meshIndex].material];
   color = material.kd;
   glm::vec3 ambient(0.0f, 0.0f, 0.0f);
   glm::vec3 diffuse(0.0f, 0.0f, 0.0f);
   glm::vec3 specular(0.0f, 0.0f, 0.0f);
   //std::cout << "mesh index: " << meshIndex << "\n";
   
   
   glm::vec3 p = ray.p + (t * ray.d);
   vec3 normal = triangleHit.getNormal(p);
   
   glm::vec3 v = ray.d * (-1.0f);
   v = v / glm::length(v);
   
   ambient = material.ka * ia;
   
   int i, j;
   /*
   glm::vec3 lightPos(-100, 100, 100);
   glm::vec3 lightColor(1.5, 1.5, 1.5);
   glm::vec3 l = (lightPos) - p;
   l = l / glm::length(l);
   
   std::cout << "n dot l: " << (fclamp(0.0f, 1.0f, glm::dot(normal,l))) << "\n";
   std::cout << "normal: <" << normal.x << ", " << normal.y << ", " << normal.z << ">\n";
   std::cout << "l: <" << l.x << ", " << l.y << ", " << l.z << ">\n\n";
   
   diffuse.x = material.kd.x * (fclamp(0.0f, 1.0f, glm::dot(normal,l))) * lightColor.x;
   diffuse.y = material.kd.y * (fclamp(0.0f, 1.0f, glm::dot(normal,l))) * lightColor.y;
   diffuse.z = material.kd.z * (fclamp(0.0f, 1.0f, glm::dot(normal,l))) * lightColor.z;
   */
   
   for (i = 0; i < emissiveMeshes.size(); i++)
   {
      Material lightMaterial = materials[emissiveMeshes[i]->material];
      vector<glm::vec3> samples = emissiveMeshes[i]->getEmissiveSamples();
      float lightPortion = 1.0f / samples.size();
      for (i = 0; i < samples.size(); i++)
      {
         glm::vec3 l = (samples[i]) - p;
         l = l / glm::length(l);
         
         std::cout << "n dot l: " << (fclamp(0.0f, 1.0f, glm::dot(normal,l))) << "\n";
         std::cout << "normal: <" << normal.x << ", " << normal.y << ", " << normal.z << ">\n";
         std::cout << "l: <" << l.x << ", " << l.y << ", " << l.z << ">\n\n";
         
         diffuse.x += lightPortion * material.kd.x * (fclamp(0.0f, 1.0f, glm::dot(normal,l))) * lightMaterial.ke.x;
         diffuse.y += lightPortion * material.kd.y * (fclamp(0.0f, 1.0f, glm::dot(normal,l))) * lightMaterial.ke.y;
         diffuse.z += lightPortion * material.kd.z * (fclamp(0.0f, 1.0f, glm::dot(normal,l))) * lightMaterial.ke.z;
         
         //specular 
      }
   }
   
   color = ambient + diffuse + specular;
   
   return color;
}



































