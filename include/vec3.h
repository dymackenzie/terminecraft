/**
 * @file vec3.h
 */

#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {
    public:
        // data attributes
        float x;
        float y;
        float z;

        /**
         * Adds two Vector3 together and returns resulting Vector3.
         * 
         * @param v1 - first vector
         * @param v2 - second vector
         */
        Vector3 add(Vector3 v1, Vector3 v2);

        /**
         * Subtracts two Vector3 (v1 - v2) and returns resulting Vector3.
         * 
         * @param v1 - first vector
         * @param v2 - second vector
         */
        Vector3 sub(Vector3 v1, Vector3 v2);

        /**
         * Multiplies all values of Vector3 by scale.
         * 
         * @param v - vector passed by parameter
         * @param s - float to scale vector by
         */
        void scale(Vector3 &v, float s);

        /**
         * Normalizes (makes length of Vector3 equal to one) passed Vector3.
         * 
         * @param v - vector to normalize
         */
        void normalize(Vector3 &v);

        /**
         * Prints vector for debugging.
         * 
         * @param v - vector to print
         */
        void print(Vector3 v);
};

#endif