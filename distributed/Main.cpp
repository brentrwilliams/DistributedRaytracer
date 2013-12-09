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
   */
   /*
   MeshData* tempMeshData;
   OBJReader objFile(objFileName);
   std:: cout << objFile.sceneBoundingBox << "\n";
   std:: cout << objFile.mtlFileName << "\n";
   int count = 0;
   Mesh* tempMesh;
   
   while (objFile.hasNextMesh())
   {
      tempMeshData = objFile.getMeshData();
      std::cout << "\n" << *tempMeshData  << "\n";
      
      if (count == 1)
      {
         tempMesh = new Mesh(*tempMeshData);
         vector<glm::vec3> samples = tempMesh->getEmissiveSamples();
         int k;
         for (k = 0; k < samples.size(); k++)
         {
            std::cout << "<" << samples[k].x << ", " << samples[k].y << ", " << samples[k].z << ">\n";
         }
      }
      count++;
   }*/
   /*
   char buffer[512];
   std::ifstream mtlFile;
   mtlFile.open(objFile.mtlFileName.c_str(), std::ifstream::in);
   while (mtlFile.good())
   {
      mtlFile.getline(buffer,512);
      std::cout << buffer << "\n";
   }*/
   
   /*
   MTLReader mtlReader(objFile.mtlFileName.c_str());
   std::map<std::string, Material> materials = mtlReader.getMaterials();
   for( std::map<std::string, Material>::iterator matIt=materials.begin(); matIt!=materials.end(); ++matIt)
   {
       cout << (*matIt).second << endl;
   }
   */
   
   return 0;
}
