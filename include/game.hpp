/**
 * @file game.hpp
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <vec3.hpp>
#include <vecs.hpp>
#include <colors.h>

using namespace std;

static const int WIDTH = 500;
static const int HEIGHT = 180;

static const float VIEW_WIDTH = 1; // in radians
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
static const char BLOCK_BORDER = '.';

class Game {
    public:

        /**
         * Default constructor, initializes player, block map, and screen.
         */
        Game();

        /**
         * Updates player view and position based on keyboard input.
         */
        void updatePlayer();

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
         * Generates picture by raytracing for each element on screen data structure.
         */
        void refreshScreen();

        /**
         * Prints out screen onto terminal.
         */
        void drawScreen();
    

    private:

        // data

        /**
         * struct for player attributes
         */ 
        struct Player {
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