/**
 * Mesh.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Mesh.hpp"

std::ostream &operator<<(std::ostream &out, Mesh mesh)
{
   out << "Mesh: " << mesh.name << "\n";
   if (!mesh.material.empty())
      out << "\tMaterial: " << mesh.material << "\n";
   
   
   //out << "(" << bb.maxs.x << ", " << bb.maxs.y << ", " << bb.maxs.z << ")";
   return out;
}
