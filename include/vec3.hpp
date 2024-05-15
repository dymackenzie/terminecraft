/**
 * @file vec3.hpp
 */

#ifndef VECTOR3_H
#define VECTOR3_H

#define EPISLON 0.000000000001

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
        bool operator == (const Vector3 &v){ 
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
        static Vector3 add(Vector3 v1, Vector3 v2);

        /**
         * Subtracts two Vector3 (v1 - v2) and returns resulting Vector3.
         * 
         * @param v1 - first vector
         * @param v2 - second vector
         */
        static Vector3 sub(Vector3 v1, Vector3 v2);

        /**
         * Multiplies all values of Vector3 by scale.
         * 
         * @param v - vector passed by parameter
         * @param s - float to scale vector by
         */
        static void scale(Vector3 &v, float s);

        /**
         * Normalizes (makes length of Vector3 equal to one) passed Vector3.
         * 
         * @param v - vector to normalize
         */
        static void normalize(Vector3 &v);

        /**
         * Prints vector for debugging.
         * 
         * @param v - vector to print
         */
        static void print(Vector3 v);
};

#endif