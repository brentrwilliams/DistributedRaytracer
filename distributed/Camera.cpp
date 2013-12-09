/**
 * Camera.cpp
 *
 * @author Brent Williams brent.robert.williams@gmail.com
 *
 */

#include "Camera.hpp"

Camera::Camera(char* fileName)
{   
   std::ifstream inFile;
   inFile.open(fileName, std::ifstream::in);
   if (!inFile.good())
   {
      std::cerr << "Unable to open file " << fileName << "\n";
      exit (EXIT_FAILURE);
   }
   read(inFile);
}

std::ostream& operator<<(std::ostream& os, const Camera& camera)
{
   os << "location: " << "< " << camera.location.x << " " << camera.location.y << " " << camera.location.z << " >\n";
   os << "up: " << "< " << camera.up.x << " " << camera.up.y << " " << camera.up.z << " >\n";
   os << "right: " << "< " << camera.right.x << " " << camera.right.y << " " << camera.right.z << " >\n";
   os << "look at: " << "< " << camera.lookAt.x << " " << camera.lookAt.y << " " << camera.lookAt.z << " >\n";
   
   return os;
}

void Camera::read(std::ifstream &inFile)
{
   char buffer[MAX_CHARS_PER_LINE], *tmp;
   float temp1, temp2, temp3;
   int result;
   
   while (inFile.good())
   {
      inFile.getline(buffer, MAX_CHARS_PER_LINE);
 
      if(strncmp(buffer, "camera", strlen("camera")) == 0)
      {
         inFile.getline(buffer, MAX_CHARS_PER_LINE);
   
         while (strcmp(buffer, "}") != 0 && inFile.good())
         {
            /*
                 location  <0, 0, 14>
                 up        <0,  1,  0>
                 right     <1.33333, 0,  0>
                 look_at   <0, 0, 0>
            */
            //cout << buffer << endl;
            
            result = sscanf(buffer, " location < %f, %f, %f > ", &temp1, &temp2, &temp3);
            if (result == 3)
            {
               location.x = temp1;
               location.y = temp2;
               location.z = temp3;
            }
            
            result = sscanf(buffer, " up < %f, %f, %f > ", &temp1, &temp2, &temp3);
            if (result == 3)
            {
               up.x = temp1;
               up.y = temp2;
               up.z = temp3;
            }
            
            result = sscanf(buffer, " right < %f, %f, %f > ", &temp1, &temp2, &temp3);
            if (result == 3)
            {
               right.x = temp1;
               right.y = temp2;
               right.z = temp3;
            }
            
            result = sscanf(buffer, " look_at < %f, %f, %f > ", &temp1, &temp2, &temp3);
            if (result == 3)
            {
               lookAt.x = temp1;
               lookAt.y = temp2;
               lookAt.z = temp3;
            }
            
                  
            inFile.getline(buffer, MAX_CHARS_PER_LINE);
         }  
      }
   }
}
