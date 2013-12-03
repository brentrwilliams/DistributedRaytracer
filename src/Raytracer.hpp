/**
 * Raytracer.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP

#include <vector>

#include "OBJReader.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

class Raytracer
{
   public:
      Raytracer(int imageWidth, int imageHeight, char* objFileName, char* cameraFileName);
      ~Raytracer();
      void trace();
      
   //private:
      int imageWidth;
      int imageHeight;
      OBJReader* objReader; 
      Camera* camera;
      std::vector<Mesh> meshes;
};

#endif
