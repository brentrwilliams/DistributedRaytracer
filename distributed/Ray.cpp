/**
 * Ray.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Ray.hpp"

Ray::Ray()
{   
}

Ray::Ray(glm::vec3 p, glm::vec3 d)
{
   this->p = p; //Point
   this->d = d; //Direction
   ior = 1.0f; //Index of Refraction
}

Ray::Ray(glm::vec3 p, glm::vec3 d, float ior)
{
   this->p = p; //Point
   this->d = d; //Direction
   this->ior = ior; //Index of Refraction
}


Ray::Ray(const Ray& ray)
{
   this->p = ray.p; //Point
   this->d = ray.d; //Direction
   ior = 1.0f; //Index of Refraction
}

void Ray::calculateRay(RayCalcInfo r, int x, int y)
{
   float u_s, v_s, w_s = -1;
   glm::vec3 sPrime;
   
   u_s = r.l + (r.r - r.l) * ((r.i + 0.1667 + (0.3333 * x)) / r.imgWidth);
   v_s = r.b + (r.t - r.b) * ((r.j + 0.1667 + (0.3333 * y)) / r.imgHeight);
   
   sPrime = r.p_0 + u_s*r.u + v_s*r.v + w_s*r.w;
   
   p = sPrime;
   d = (sPrime - r.p_0);
   d = d / glm::length(d);
}

void Ray::toObjectSpace(glm::mat4 invTrans)
{
   glm::vec4 tempP(p.x, p.y, p.z, 1.0f);
   glm::vec4 tempD(d.x, d.y, d.z, 0.0f);
   
   tempP = invTrans * tempP;
   tempD = invTrans * tempD;
   
   p.x = tempP.x;
   p.y = tempP.y;
   p.z = tempP.z;
   
   d.x = tempD.x;
   d.y = tempD.y;
   d.z = tempD.z;
}

std::ostream& operator<<(std::ostream& os, const Ray& ray)
{
   os << "point: " << "< " << ray.p.x << " " << ray.p.y << " " << ray.p.z << " >\n";
   os << "direction: " << "< " << ray.d.x << " " << ray.d.y << " " << ray.d.z << " >\n";
  
   return os;
}
