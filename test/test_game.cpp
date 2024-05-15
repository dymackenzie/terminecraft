/**
 * @file test_game.cpp
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "game.cpp"

TEST_CASE( "isRayOutside", "[Game]" ) {
    Game game = Game();
    Vector3 v = Vector3(2, 4, 6);
    Vector3 v1 = Vector3(17, 0, 0);
    Vector3 v2 = Vector3(0, 17, 0);
    Vector3 v3 = Vector3(0, 0, 17);
    Vector3 v4 = Vector3(-1, 0, 0);
    Vector3 v5 = Vector3(0, -1, 0);
    Vector3 v6 = Vector3(0, 0, -1);
    REQUIRE( game.isRayOutside(v) == false );
    REQUIRE( game.isRayOutside(v1) == true );
    REQUIRE( game.isRayOutside(v2) == true );
    REQUIRE( game.isRayOutside(v3) == true );
    REQUIRE( game.isRayOutside(v4) == true );
    REQUIRE( game.isRayOutside(v5) == true );
    REQUIRE( game.isRayOutside(v6) == true );
}

TEST_CASE( "onBlockBorder", "[Game]" ) {
    Game game = Game();
    Vector3 v1 = Vector3(0.02, 0.02, 0);
    Vector3 v2 = Vector3(0.02, 0.04, 0.04);
    Vector3 v3 = Vector3(1.02, 1.04, 1.04);
    Vector3 v4 = Vector3(0.02, 1.04, 0.02);
    REQUIRE( game.onBlockBorder(v1) == true);
    REQUIRE( game.onBlockBorder(v2) == false);
    REQUIRE( game.onBlockBorder(v3) == false);
    REQUIRE( game.onBlockBorder(v4) == true);
}