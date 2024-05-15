/**
 * @file vecs.h
 */

#ifndef VECTORS_H
#define VECTORS_H

#include <vec3.h>

class VectorS {
    public:
        // data attributes
        // phi is for 360 degree view on a horizontal plane, is
        // zero when facing the x-axis
        float phi;
        // theta is the 180 degree view on the vertical plane between
        // +z and -z axises
        float theta;

        /**
         * Default constructor constructs with angles facing the x-axis.
         */
        VectorS() {
            phi = 0;
            theta = 0;
        }

        /**
         * Constructor based off given parameters.
         */
        VectorS(float pphi, float ptheta) {
            phi = pphi;
            theta = ptheta;
        }

        /**
         * Converts VectorS angles to position on the unit circle in x, y, and z
         * coordinates. 
         * 
         * @param a - VectorS class holding both angles
         */
        Vector3 anglesToVect(VectorS a);
};

#endif