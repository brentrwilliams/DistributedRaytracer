/**
 * Utilities.hpp
 * 
 * @author Brent Williams brent.robert.williams@gmail.com
 */ 

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <cmath>

float fclamp(float min, float max, float val);

bool fEqual(float valA, float valB, float tolerance);

bool vec3Equal(glm::vec3 val1, glm::vec3 val2, float tolerance);

#endif
