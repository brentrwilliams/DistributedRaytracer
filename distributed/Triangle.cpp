/**
 * Triangle.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Triangle.hpp"

Triangle::Triangle()
{
   type = TRIANGLE_TYPE;
}

Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec2 uv1, glm::vec2 uv2, glm::vec2 uv3)
{
   type = TRIANGLE_TYPE;
   this->v1 = v1;
   this->v2 = v2;
   this->v3 = v3;
   
   this->uv1 = uv1;
   this->uv2 = uv2;
   this->uv3 = uv3;
   
   calculateBoundingBox();
}

std::ostream& operator<<(std::ostream& os, const Triangle& triangle)
{
   os << "v1: " << "< " << triangle.v1.x << " " << triangle.v1.y << " " << triangle.v1.z << " >\n";
   os << "v2: " << "< " << triangle.v2.x << " " << triangle.v2.y << " " << triangle.v2.z << " >\n";
   os << "v3: " << "< " << triangle.v3.x << " " << triangle.v3.y << " " << triangle.v3.z << " >\n";
   os << "uv1: " << "< " << triangle.uv1.x << " " << triangle.uv1.y << " >\n";
   os << "uv2: " << "< " << triangle.uv2.x << " " << triangle.uv2.y << " >\n";
   os << "uv3: " << "< " << triangle.uv3.x << " " << triangle.uv3.y << " >\n";
   os << "bounding box: " << triangle.boundingBox << "\n";
   
   return os;
}

bool Triangle::intersect(Ray ray, float *t)
{
   float a, b, c, d, e, f, g, h, i, j, k, l, M, beta, gamma;
   float ei_minus_hf, gf_minus_di, dh_minus_eg, ak_minus_jb, jc_minus_al, bl_minus_kc;
   
   a = v1.x - v2.x;
   b = v1.y - v2.y;
   c = v1.z - v2.z;
   
   d = v1.x - v3.x;
   e = v1.y - v3.y;
   f = v1.z - v3.z;
   
   g = ray.d.x;
   h = ray.d.y;
   i = ray.d.z;
   
   j = v1.x - ray.p.x;
   k = v1.y - ray.p.y;
   l = v1.z - ray.p.z;
   
   ei_minus_hf = (e*i - h*f);
   gf_minus_di = (g*f - d*i);
   dh_minus_eg = (d*h - e*g);
   
   ak_minus_jb = (a*k - j*b);
   jc_minus_al = (j*c - a*l);
   bl_minus_kc = (b*l - k*c);
   
   M = a*ei_minus_hf + b*gf_minus_di + c*dh_minus_eg;
   
   *t = - (f*ak_minus_jb + e*jc_minus_al + d*bl_minus_kc) / M;
   if ((*t) < 0)
      return false;
   
   gamma = (i*ak_minus_jb + h*jc_minus_al + g*bl_minus_kc) / M;
   if (gamma < 0 || gamma > 1)
      return false;
      
   beta = (j*ei_minus_hf + k*gf_minus_di + l*dh_minus_eg) / M;
   if (beta < 0 || beta > 1 - gamma)
      return false;
   
   
   return true;
}

void Triangle::calculateFaceNormal()
{
   glm::vec3 b1 = v1 - v2;
   glm::vec3 b2 = v2 - v3;
   glm::vec3 normal = glm::cross(b1, b2);
   
   faceNormal = normal / glm::length(normal);
}

glm::vec3 Triangle::getNormal(glm::vec3 pt)
{
   /*float alpha, beta, gamma;
   glm::vec3 normal;
   calculateBarycentricCoordinates(&alpha, &beta, &gamma, pt);
   normal = normal1 * alpha + normal2 * beta + normal3 * gamma;
   return normal;
   */
   return faceNormal;
}

void Triangle::calculateBoundingBox()
{
   boundingBox.mins.x = v1.x;
   boundingBox.mins.y = v1.y;
   boundingBox.mins.z = v1.z;
   
   boundingBox.maxs.x = v1.x;
   boundingBox.maxs.y = v1.y;
   boundingBox.maxs.z = v1.z;
   
   if (v2.x < boundingBox.mins.x)
      boundingBox.mins.x = v2.x;
   if (v3.x < boundingBox.mins.x)
      boundingBox.mins.x = v3.x;
   
   if (v2.y < boundingBox.mins.y)
      boundingBox.mins.y = v2.y;
   if (v3.y < boundingBox.mins.y)
      boundingBox.mins.y = v3.y;
   
   if (v2.z < boundingBox.mins.z)
      boundingBox.mins.z = v2.z;
   if (v3.z < boundingBox.mins.z)
      boundingBox.mins.z = v3.z;
   
   if (v2.x > boundingBox.maxs.x)
      boundingBox.maxs.x = v2.x;
   if (v3.x > boundingBox.maxs.x)
      boundingBox.maxs.x = v3.x;
   
   if (v2.y > boundingBox.maxs.y)
      boundingBox.maxs.y = v2.y;
   if (v3.y > boundingBox.maxs.y)
      boundingBox.maxs.y = v3.y;
   
   if (v2.z > boundingBox.maxs.z)
      boundingBox.maxs.z = v2.z;
   if (v3.z > boundingBox.maxs.z)
      boundingBox.maxs.z = v3.z;
   
   boundingBox.calculateCorners();

   int i;
   //for (i = 0; i < 8; i++)
   //   printf("\tcorner[%d]: <%f, %f, %f>\n", i, boundingBox.corner[i].x, boundingBox.corner[i].y, boundingBox.corner[i].z); 

   //printf("Triangle center: <%f, %f, %f>\n", boundingBox.center.x, boundingBox.center.y, boundingBox.center.z); 

   //for (i = 0; i < 8; i++)
   //   printf("\tcorner[%d]: <%f, %f, %f>\n", i, boundingBox.corner[i].x, boundingBox.corner[i].y, boundingBox.corner[i].z); 
}

glm::vec2 Triangle::getUV(glm::vec3 pt)
{
   glm::vec3 n, na, nb;
   glm::vec2 uv;
   float alpha, beta, gamma, lengthN;
   
   n = glm::cross((v2 - v1), (v3 - v1));
   na = glm::cross((v3 - v2), (pt - v2));
   nb = glm::cross((v2 - v1), (pt - v1));
   lengthN = glm::length(n);
   
   alpha = glm::dot(n, na) / (lengthN*lengthN);
   beta = glm::dot(n, nb) / (lengthN*lengthN);
   gamma = (1-alpha-beta);
   
   uv.x = uv1.x + beta*(uv3.x-uv1.x) + gamma*(uv2.x-uv1.x);
   uv.y = uv1.y + beta*(uv3.y-uv1.y) + gamma*(uv2.y-uv1.y);
   
   return uv;
}

void Triangle::calculateBarycentricCoordinates(float *alpha, float* beta, float* gamma, glm::vec3 p)
{
   glm::vec3 newV0 = v2 - v1, newV1 = v3 - v1, newV2 = p - v1;
   float d00 = glm::dot(newV0, newV0);
   float d01 = glm::dot(newV0, newV1);
   float d11 = glm::dot(newV1, newV1);
   float d20 = glm::dot(newV2, newV0);
   float d21 = glm::dot(newV2, newV1);
   float denom = d00 * d11 - d01 * d01;
   *beta = (d11 * d20 - d01 * d21) / denom;
   *gamma = (d00 * d21 - d01 * d20) / denom;
   *alpha = 1.0f - *beta - *gamma;
}

//Returns true if greater than
bool xAxisSort(Triangle tri1, Triangle tri2)
{
   return tri1.boundingBox.mins.x < tri2.boundingBox.mins.x;
}
bool yAxisSort(Triangle tri1, Triangle tri2)
{
   return tri1.boundingBox.mins.y < tri2.boundingBox.mins.y;
}
bool zAxisSort(Triangle tri1, Triangle tri2)
{
   return tri1.boundingBox.mins.z < tri2.boundingBox.mins.z;
}
