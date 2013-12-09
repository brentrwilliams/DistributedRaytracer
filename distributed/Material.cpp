/**
 * Material.cpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#include "Material.hpp"

Material::Material()
{
   illum = 0;
   ka = glm::vec3(0.0f);
   kd = glm::vec3(0.0f);
   ks = glm::vec3(0.0f);
   ke = glm::vec3(0.0f);
   ns = 10;
}

Material::~Material()
{
}

std::ostream &operator<<(std::ostream &out, Material material)
{
   out << material.name << ": \n";
   out << "\tillum: " << material.illum << "\n";
   out << "\tKa: <" << material.ka.x << ", " << material.ka.y << ", " << material.ka.z << ">\n";
   out << "\tKd: <" << material.kd.x << ", " << material.kd.y << ", " << material.kd.z << ">\n";
   out << "\tKs: <" << material.ks.x << ", " << material.ks.y << ", " << material.ks.z << ">\n";
   out << "\tKe: <" << material.ke.x << ", " << material.ke.y << ", " << material.ke.z << ">\n";
   out << "\tNs: " << material.ns << "\n";
   
   return out;
}

bool Material::isEmissive()
{
   return (ke.x != 0.0f || ke.y != 0.0f || ke.z != 0.0f);
}
