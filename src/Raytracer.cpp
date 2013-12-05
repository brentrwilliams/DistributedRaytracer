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
      tempMesh = new Mesh(*tempMeshData);
      std::cout << "\n" << *tempMesh  << "\n";
      meshes.push_back(tempMesh);
   }
   
   vector<glm::vec3> samples = meshes[1]->getEmissiveSamples();
   for (i = 0; i < samples.size(); i++)
   {
      std::cout << "<" << samples[i].x << ", " << samples[i].y << ", " << samples[i].z << ">\n"; 
   }
   
   std::cout << "Num meshes: " << meshes.size() << "\n";
   
   //Find all emissive meshes
   for (i = 0; i < meshes.size(); i++)
   {
      Material currMaterial = materials[meshes[i]->material];
      if (currMaterial.isEmissive())
         emissiveMeshes.push_back(meshes[i]);
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
   float t;
   Triangle* triangleHit;
   vec3 color(0.0f, 0.0f, 0.0f);
   
   intersected = intersectGeometry(ray, &t, triangleHit);
   
   if (intersected && t < (*zValue)) 
   {
      color.x = 1.0;
      color.y = 1.0;
      color.z = 1.0;
   }
   
   return color;
}

bool Raytracer::intersectGeometry(Ray ray, float *t, Triangle* triangleHit)
{
   int i, j;
   float currT;
   Mesh* currMesh;
   bool hit = false;
   for (i = 0; i < meshes.size(); i++)
   {
      currMesh = meshes[i];
      
      if (currMesh->boundingBox.intersect(ray))
      {
         for (j = 0; j < currMesh->triangles.size(); j++)
         {
            if(currMesh->triangles[j].intersect(ray, &currT))
            {
               hit = true;
               
               if (currT < (*t))
               {
                  *t = currT;
                  *triangleHit = currMesh->triangles[j];
               }
               
            }
         }
      }
   }
   return hit;
}

