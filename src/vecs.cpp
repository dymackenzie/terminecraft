/**
 * @file vecs.cpp
 */

#include <math.h>
#include <vecs.h>

/**
 * Converts VectorS angles to position on the unit circle in x, y, and z
 * coordinates. 
 * 
 * @param a - VectorS class holding both angles
 */
Vector3 VectorS::anglesToVect(VectorS a) {
    Vector3 temp;
	temp.x = cos(a.theta) * cos(a.phi);
	temp.y = cos(a.theta) * sin(a.phi);
	temp.z = sin(a.theta);
	return temp;
}