/**
 * Main.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Main.hpp"

int main(int argc, char* argv[])
{
   if (argc < 2)
   {
      std::cerr << "Invalid number of arguments\n";
      exit (EXIT_FAILURE);
   }
   
   std::vector<Mesh> meshes;
   Mesh tempMesh;
   OBJReader objFile(argv[1]);
   std:: cout << objFile.sceneBoundingBox << "\n";
   std:: cout << objFile.mtlFileName << "\n";
   
   tempMesh = objFile.getMesh();
   /*while (objFile.hasNextMesh())
   {
      meshes.push_back(tempMesh);
      tempMesh = objFile.getMesh();
   }*/
   
   
   return 0;
}
