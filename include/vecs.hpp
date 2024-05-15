/**
 * @file vecs.hpp
 */

#ifndef VECTORS_H
#define VECTORS_H

#include <vec3.hpp>

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
         * Overrides the equality operator
         */
        bool const operator == (const VectorS &v) const { 
            if (fabs(phi - v.phi) < EPISLON && 
                fabs(theta - v.theta) < EPISLON)
                return true; 
            return false; 
        }

        /**
         * Converts VectorS angles to position on the unit circle in x, y, and z
         * coordinates. 
         * 
         * @param a - VectorS class holding both angles
         */
        static Vector3 anglesToVect(VectorS a) {
            Vector3 temp;
            temp.x = cos(a.theta) * cos(a.phi);
            temp.y = cos(a.theta) * sin(a.phi);
            temp.z = sin(a.theta);
            return temp;
        }

        /**
         * Adds two VectorS classes,
         * format: (a1 + a2)
         * 
         * @param a1 - first VectorS to add
         * @param a2 - second VectorS to add
         */
        static VectorS add(VectorS a1, VectorS a2) {
            VectorS temp;
            temp.phi = a1.phi + a2.phi;
            temp.theta = a1.theta + a2.theta;
            return temp;
        }
};

#endif