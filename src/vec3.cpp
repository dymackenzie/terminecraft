/**
 * @file vec3.cpp
 */

#include <math.h>
#include <vec3.h>
#include <iostream>

/**
 * Adds two Vector3 together and returns resulting Vector3.
 * 
 * @param v1 - first vector
 * @param v2 - second vector
 */
Vector3 add(Vector3 v1, Vector3 v2) {
    Vector3 temp;
    temp.x = v1.x + v2.x;
    temp.y = v1.y + v2.y;
    temp.z = v1.z + v2.z;
    return temp;
}

/**
 * Subtracts two Vector3 (v1 - v2) and returns resulting Vector3.
 * 
 * @param v1 - first vector
 * @param v2 - second vector
 */
Vector3 sub(Vector3 v1, Vector3 v2) {
    Vector3 temp;
    temp.x = v1.x - v2.x;
    temp.y = v1.y - v2.y;
    temp.z = v1.z - v2.z;
    return temp;
}

/**
 * Multiplies all values of Vector3 by scale.
 * 
 * @param v - vector passed by parameter
 * @param s - float to scale vector by
 */
void scale(Vector3 &v, float s) {
    v.x *= s;
    v.y *= s;
    v.z *= s;
}

/**
 * Normalizes (makes length of Vector3 equal to one) passed Vector3.
 * 
 * @param v - vector to normalize
 */
void normalize(Vector3 &v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    v.x /= length;
    v.y /= length;
    v.z /= length;
}

/**
 * Prints vector for debugging.
 * 
 * @param v - vector to print
 */
void print(Vector3 v) {
    std::cout << "x = " << v.x << " y = " << v.y << " z = " << v.z << std::endl;
}


