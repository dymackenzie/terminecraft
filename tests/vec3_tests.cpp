/**
 * @file vec3_tests.cpp
 */

#include "catch.hpp"
#include "vec3.hpp"

TEST_CASE( "Vector3 addition", "[Vector3]" ) {
    Vector3 x = Vector3(1, 2, 3);
    Vector3 y = Vector3(0.1, 0.2, 0.3);
    Vector3 z = Vector3(-1, -2, -3);
    REQUIRE( Vector3::add(x, z) == Vector3() );
    REQUIRE( Vector3::add(x, y) == Vector3(1.1, 2.2, 3.3) );
    REQUIRE( Vector3::add(z, y) == Vector3(-0.9, -1.8,-2.7) );
}