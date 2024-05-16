/**
 * @file test_vecs.cpp
 */

#include "catch.hpp"
#include "vecs.hpp"

TEST_CASE("VectorS operations", "[VectorS]")
{
    VectorS a = VectorS();
    VectorS a2 = VectorS(M_PI / 2, M_PI / 2);
    Vector3 v = VectorS::anglesToVect(a);
    Vector3 v2 = VectorS::anglesToVect(a2);

    SECTION("angles to vector")
    {
        REQUIRE(v == Vector3(1, 0, 0));
        REQUIRE(v2 == Vector3(0, 0, 1));
    }
    SECTION("vector addition")
    {
        REQUIRE(VectorS::add(a, a2) == VectorS(M_PI / 2, M_PI / 2));
    }
}