/**
 * Main.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Main.hpp"

int main(int argc, char* argv[])
{
   if (argc < 5)
   {
      std::cerr << "Invalid number of arguments\n";
      exit (EXIT_FAILURE);
   }
   
   int imageWidth = atoi(argv[1]);
   int imageHeight = atoi(argv[2]); 
   char* objFileName = argv[3];
   char* cameraFileName = argv[4];
   
   Raytracer raytracer(imageWidth, imageHeight, objFileName, cameraFileName);
   
   /*
   Camera camera(argv[2]);
   
   std::cout << camera << "\n"; 
   
   std::vector<Mesh*> meshes;
   Mesh* tempMesh;
   OBJReader objFile(argv[1]);
   std:: cout << objFile.sceneBoundingBox << "\n";
   std:: cout << objFile.mtlFileName << "\n";
   
   tempMesh = objFile.getMesh();
   //std::cout << "\n" << *tempMesh  << "\n";
   while (objFile.hasNextMesh())
   {
      std::cout << "\n" << *tempMesh  << "\n";
      meshes.push_back(tempMesh);
      tempMesh = objFile.getMesh();
   }
   */
   
   
   
   return 0;
}
