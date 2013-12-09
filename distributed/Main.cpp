/**
 * Main.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Main.hpp"

int main(int argc, char* argv[])
{
   int  numtasks, rank, len, rc; 
   char hostname[MPI_MAX_PROCESSOR_NAME];
   
   rc = MPI_Init(&argc,&argv);
   if (rc != MPI_SUCCESS) 
   {
     std::cerr << "Error starting MPI program. Terminating.\n";
     MPI_Abort(MPI_COMM_WORLD, rc);
   }
   
   if (argc < 6)
   {
      std::cerr << "Invalid number of arguments\n";
      exit(EXIT_FAILURE);
   }
   
   MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   MPI_Get_processor_name(hostname, &len);
   
   std::cout << rank << ": " << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4] << " " << argv[5] << "\n\n"; 
   
   int imageWidth = atoi(argv[1]);
   int imageHeight = atoi(argv[2]); 
   char* objFileName = new char[256];
   strcpy(objFileName, argv[3]);
   char* cameraFileName = new char[256];
   strcpy(cameraFileName,argv[4]);
   char* outputFileName = new char[256];
   strcpy(outputFileName, argv[5]);
   
   printf ("Number of tasks= %d My rank= %d Running on %s\n", numtasks,rank,hostname);
   
   Raytracer raytracer(imageWidth, imageHeight, objFileName, cameraFileName);
   raytracer.trace();
   raytracer.saveImage(outputFileName);
   
   MPI_Finalize();
   return 0;
}
