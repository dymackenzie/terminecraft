/**
 * @file game.hpp
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <vec3.hpp>
#include <vecs.hpp>
#include <colors.h>
#include <bits/stdc++.h>

using namespace std;

static const int WIDTH = 500;
static const int HEIGHT = 180;

static const float VIEW_WIDTH = 1;    // in radians
static const float VIEW_HEIGHT = 0.7; // in radians

// speed of player and view rotation speed
static const float SPEED = 0.15;
static const float TILT = 0.03;

static const int CHUNK_X = 16;
static const int CHUNK_Y = 16;
static const int CHUNK_Z = 16;
static const int DEPTH = 4;

static const float EYE_HEIGHT = 1.5;

// starting position of player
static const int START_X = 5;
static const int START_Y = 5;
static const int START_Z = DEPTH + EYE_HEIGHT;

static const float BLOCK_BORDER_WIDTH = 0.03;
static const char BLOCK_FILL = '@';
static const char BLOCK_HIGHLIGHT = 'o';
static const char BLOCK_BORDER = '.';

class Game
{
public:
    /**
     * Default constructor, initializes player, block map, and screen.
     */
    Game()
    {
        initMap();
        fillMap();
        initScreen();
        initPlayer();
    }

    /**
     * Customized constructor.
     */
    Game(Vector3 ppos, VectorS pview)
    {
        *this = Game();
        player.pos = ppos;
        player.view = pview;
    }

    /**
     * Runs all necessary game logic.
     */
    void run();

    /**
     * Updates player view and position based on keyboard input.
     */
    void updatePlayer();

    /**
     * Generates picture by raytracing for each element on screen data structure.
     */
    void refreshScreen();

    /**
     * Prints out screen onto terminal.
     */
    void drawScreen();

    /**
     * Get block player is pointing at,
     * basically like raytracing except for the middle ray and
     * the function returns position of the block player is pointing at
     */
    Vector3 getBlock();

    /**
     * Place a block on the face the player is pointing at, it does this
     * by finding the closest face the player is pointing at and then
     * places block in respective location.
     * Block faces 0-5: x+, x-, y+, y-, z+, z-
     */
    void placeBlock(Vector3 curr);

    /**
     * If ray is outside bounds of border, return true.
     *
     * @param v - vector to check
     */
    bool isRayOutside(Vector3 v);

    /**
     * If vector is within block border size on two axis, return true.
     *
     * @param v - vector to check
     */
    bool onBlockBorder(Vector3 v);

    /**
     * Returns block_map
     */
    vector<vector<char>> getBlockMap()
    {
        return block_map;
    }

    /**
     * Returns screen structure
     */
    vector<vector<char>> getScreen()
    {
        return screen;
    }

private:
    // data

    /**
     * struct for player attributes
     */
    struct Player
    {
        Vector3 pos;
        VectorS view;
    } player;

    /**
     * Two dimensional array to hold block locations,
     * stored in z-slices.
     *
     * Order: [z][x][y]
     */
    vector<vector<char>> block_map;

    /**
     * Two dimensional array to respresent screen on terminal.
     *
     * Order: [x][y]
     */
    vector<vector<char>> screen;

    // functions

    /**
     * Initializes initial block map.
     */
    void initMap();

    /**
     * Initializes initial screen size.
     */
    void initScreen();

    /**
     * Fills the existing block map up with blocks.
     *
     * @pre - the block map must already be initialized.
     */
    void fillMap();

    /**
     * Initializes player position and view area.
     */
    void initPlayer();

    /**
     * Helper function to both calculate how much to increment raytrace by, keeping it
     * clamped to 2 or below.
     *
     * @param position - given position of raytrace
     * @param dir - given direction of raytrace
     */
    float raytraceIncrement(Vector3 position, Vector3 dir);

    /**
     * Initializes the initial ray tracing directions for each pixel on screen
     */
    vector<vector<Vector3>> initDir();

    /**
     * Raytraces from given initial direction until it hits a block.
     *
     * @param dir - initial direction to raytrace from.
     */
    char raytracing(Vector3 dir);

    /**
     * Helper function to convert x and y indices into index for singular array.
     */
    int convertCoordinates(int x, int y);
};

#endif