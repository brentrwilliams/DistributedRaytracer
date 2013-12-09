/**
 * Image.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Image.hpp"

Image::Image()
{
}

Image::Image(int width, int height)
{
   allocateImage(width, height);
}

void Image::allocateImage(int width, int height)
{
   int i;
   
   this->width = width;
   this->height = height;
   
   r = (float **) malloc(width*sizeof(float*));
   for (i = 0; i < width; i++)
      r[i] = (float *) malloc(height*sizeof(float));

   g = (float **) malloc(width*sizeof(float*));
   for (i = 0; i < width; i++)
      g[i] = (float *) malloc(height*sizeof(float));
   
   b = (float **) malloc(width*sizeof(float*));
   for (i = 0; i < width; i++)
      b[i] = (float *) malloc(height*sizeof(float));
}

void Image::readTGA(char *filename)
{
   FILE *fptr;
   TGAHeader header;
   int x, y;
   size_t result;   
   
   fptr = fopen(filename,"r");
   
   if (fptr == NULL)
   {
      cerr << "File error\n";
      exit(1);
   }
   
   //Read header data
   header.idlength = fgetc(fptr);
   header.colourmaptype = fgetc(fptr);
   header.datatypecode = fgetc(fptr);
   
   if (header.datatypecode != 2)
   {
      cerr << "Unable to read TGA file.\n" << "This reader can only read uncompressed, 24-bit RGB images.\n";
      exit(1);
   }
   
   result = fread(&header.colourmaporigin,2,1,fptr);
   result = fread(&header.colourmaplength,2,1,fptr);
   header.colourmapdepth = fgetc(fptr);
   
   result = fread(&header.x_origin,2,1,fptr);
   result = fread(&header.y_origin,2,1,fptr);
   
   result = fread(&header.width,2,1,fptr);
   result = fread(&header.height,2,1,fptr);
   width = header.width;
   height = header.height;
   
   header.bitsperpixel = fgetc(fptr);
   header.imagedescriptor = fgetc(fptr);
   if (header.bitsperpixel != 24)
   {
      cerr << "Unable to read TGA file.\n" << "This reader can only read uncompressed, 24-bit RGB images.\n";
      exit(1);
   }
   
   if (width > 0 && height > 0)
      allocateImage(width, height);
      
   //Read the RGB values
   for (y = 0; y < height; y++)
   {
      for (x = 0; x < width; x++)
      {
         b[x][y] = ((float)fgetc(fptr)) / 255.0f;
         g[x][y] = ((float)fgetc(fptr)) / 255.0f;
         r[x][y] = ((float)fgetc(fptr)) / 255.0f;
      }
   }
}

/**
 * Writes out the image
 * 
 * Note: The bottom left corner is (0, 0)
 **/
void Image::writeTGA(char *filename)
{
   FILE *fp;
   int x, y;
   fp = fopen(filename, "w");
   if (!fp)
   {
     printf("File %s could not be written to.\n", filename);
     exit(EXIT_FAILURE);
   }
   
   //Write Header
   fputc(0,fp);
   fputc(0,fp);
   
   /* uncompressed RGB */
   fputc(2,fp);                         
   fputc(0,fp); 
   fputc(0,fp);
   fputc(0,fp); 
   fputc(0,fp);
   fputc(0,fp);
   
   /* X origin */
   fputc(0,fp); 
   fputc(0,fp);           
   /* y origin */
   fputc(0,fp); 
   fputc(0,fp);
   
   /* width and height */           
   fputc((width & 0x00FF),fp);
   fputc((width & 0xFF00) / 256,fp);
   fputc((height & 0x00FF),fp);
   fputc((height & 0xFF00) / 256,fp);
   
   /* 24 bit bitmap */
   fputc(24,fp);                        
   fputc(0,fp);
   
   //Write Data
   for (y = 0; y < height; y++)
   {
      for (x = 0; x < width; x++)
      {
         /* B (Blue) value */
         fputc(((char)(b[x][y]*255)),fp);
         /* G (Green) value */
         fputc(((char)(g[x][y]*255)),fp);
         /* R (Red) value */
         fputc(((char)(r[x][y]*255)),fp);
      }
   }
   
   fclose(fp);
      
}

void Image::scaleColors()
{
   int i, j;
   float colorMax = 0.000001;
   
   for (i = 0; i < width; i++)
   {
      for (j = 0; j < height; j++)
      {
         if(r[i][j] > colorMax)
            colorMax = r[i][j];
         if(g[i][j] > colorMax)
            colorMax = g[i][j];
         if(b[i][j] > colorMax)
            colorMax = b[i][j];
      }
   }
   
   for (i = 0; i < width; i++)
   {
      for (j = 0; j < height; j++)
      {
         r[i][j] /= colorMax;
         g[i][j] /= colorMax;
         b[i][j] /= colorMax;
      }
   }
}

vec3 Image::getColor(int x, int y)
{
   return vec3(r[x][y], g[x][y], b[x][y]);
}
