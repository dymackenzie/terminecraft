/**
 * @file vec3.hpp
 */

#ifndef VECTOR3_H
#define VECTOR3_H

#include "iostream"
#include "math.h"

#define EPISLON 0.0000001

class Vector3 {
    public:
        // data attributes
        float x;
        float y;
        float z;

        /**
         * Default constructor for Vector3 class.
         */
        Vector3() {
            x = 0;
            y = 0;
            z = 0;
        }

        /**
         * Constructor for Vector3 class.
         */
        Vector3(float px, float py, float pz) {
            x = px;
            y = py;
            z = pz;
        }

        /**
         * Overrides the equality operator
         */
        bool operator == (const Vector3 &v) const { 
            if (fabs(x - v.x) < EPISLON && 
                fabs(y - v.y) < EPISLON &&
                fabs(z - v.z) < EPISLON) 
                return true; 
            return false; 
        }

        /**
         * Adds two Vector3 together and returns resulting Vector3.
         * 
         * @param v1 - first vector
         * @param v2 - second vector
         */
        static Vector3 add(Vector3 v1, Vector3 v2) {
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
        static Vector3 sub(Vector3 v1, Vector3 v2) {
            Vector3 temp;
            temp.x = v1.x - v2.x;
            temp.y = v1.y - v2.y;
            temp.z = v1.z - v2.z;
            return temp;
        }

        /**
         * Multiplies all values of Vector3 by scale.
         * 
         * @param v - vector passed by value
         * @param s - float to scale vector by
         */
        static Vector3 scale(Vector3 v, float s) {
            v.x *= s;
            v.y *= s;
            v.z *= s;
            return v;
        }

        /**
         * Normalizes (makes length of Vector3 equal to one) passed Vector3.
         * 
         * @param v - vector to normalize
         */
        static Vector3 normalize(Vector3 v) {
            float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
            v.x /= length;
            v.y /= length;
            v.z /= length;
            return v;
        }

        /**
         * Prints vector for debugging.
         * 
         * @param v - vector to print
         */
        static void print(Vector3 v) {
            std::cout << "x = " << v.x << " y = " << v.y << " z = " << v.z << std::endl;
        }
};

#endif