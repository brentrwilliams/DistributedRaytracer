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
   objReader  = new OBJReader(objFileName);
   camera = new Camera(cameraFileName);
}

Raytracer::~Raytracer()
{
   delete objReader;
   delete camera;
}

void Raytracer::trace()
{
   
}
