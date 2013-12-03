/**
 * Main.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Main.hpp"

int main(int argc, char* argv[])
{
   if (argc < 6)
   {
      std::cerr << "Invalid number of arguments\n";
      exit (EXIT_FAILURE);
   }
   
   int imageWidth = atoi(argv[1]);
   int imageHeight = atoi(argv[2]); 
   char* objFileName = argv[3];
   char* cameraFileName = argv[4];
   char* outputFileName = argv[5];
   
   Raytracer raytracer(imageWidth, imageHeight, objFileName, cameraFileName);
   raytracer.trace();
   raytracer.saveImage(outputFileName);
   
   /*
   Camera camera(cameraFileName);
   
   std::cout << camera << "\n"; 
   
   std::vector<Mesh*> meshes;
   Mesh* tempMesh;
   OBJReader objFile(objFileName);
   std:: cout << objFile.sceneBoundingBox << "\n";
   std:: cout << objFile.mtlFileName << "\n";
   
   while (objFile.hasNextMesh())
   {
      tempMesh = objFile.getMesh();
      std::cout << "\n" << *tempMesh  << "\n";
      meshes.push_back(tempMesh);
   }
   */
   return 0;
}
