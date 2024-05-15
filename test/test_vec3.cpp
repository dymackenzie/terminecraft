/**
 * @file test_vec3.cpp
 */

#include "catch.hpp"
#include "vec3.hpp"

TEST_CASE( "Vector3 operations", "[Vector3]" ) {
    Vector3 x = Vector3(1, 2, 3);
    Vector3 y = Vector3(0.1, 0.2, 0.3);
    Vector3 z = Vector3(-1, -2, -3);

    SECTION( "adding" ) {
        REQUIRE( Vector3::add(x, z) == Vector3() );
        REQUIRE( Vector3::add(x, y) == Vector3(1.1, 2.2, 3.3) );
        REQUIRE( Vector3::add(z, y) == Vector3(-0.9, -1.8,-2.7) );
    }
    SECTION( "subtracting" ) {
        REQUIRE( Vector3::sub(x, z) == Vector3(2, 4, 6) );
        REQUIRE( Vector3::sub(x, y) == Vector3(0.9, 1.8, 2.7) );
        REQUIRE( Vector3::sub(z, y) == Vector3(-1.1, -2.2,-3.3) );
    }
    SECTION( "scaling" ) {
        REQUIRE( Vector3::scale(x, 2) == Vector3(2, 4, 6) );
        REQUIRE( Vector3::scale(y, 3) == Vector3(0.3, 0.6, 0.9) );
        REQUIRE( Vector3::scale(z, 2) == Vector3(-2, -4, -6) );
    }
    SECTION( "normalizing" ) {
        Vector3 n = Vector3::normalize(x);
        float length = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
        REQUIRE( fabs(length - 1) < EPISLON );
    }
}