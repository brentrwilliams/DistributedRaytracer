/**
 * Raytracer.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <vector>
#include <map>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "OBJReader.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Ray.hpp"
#include "Image.hpp"
#include "Material.hpp"
#include "MTLReader.hpp"

#define MAX_FLOAT 1000000.0

class Raytracer
{
   public:
      Raytracer(int imageWidth, int imageHeight, char* objFileName, char* cameraFileName);
      ~Raytracer();
      void trace();
      void saveImage(char *imageName);
      
   //private:
      int imageWidth;
      int imageHeight;
      OBJReader* objReader; 
      Camera* camera;
      std::vector<Mesh*> meshes;
      std::vector<Mesh*> emissiveMeshes;
      std::map<std::string, Material> materials;
      Image image;
      float **zBuffer;
      
      glm::vec3 calculatePixelColor(RayCalcInfo rayCalcInfo, int i, int j);
      glm::vec3 traceRay(Ray &ray, float *zValue);
      bool intersectGeometry(Ray ray, float *t, Triangle* triangleHit);
};

#endif
