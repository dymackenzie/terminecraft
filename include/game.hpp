/**
 * @file game.hpp
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <vec3.hpp>
#include <vecs.hpp>

using namespace std;

const int WIDTH = 500;
const int HEIGHT = 180;

const int VIEW_WIDTH = 1; // in radians
const int VIEW_HEIGHT = 0.7; // in radians

// speed of player and view rotation speed
const float SPEED = 0.15;
const float TILT = 0.03;

const int BLOCK_X = 16;
const int BLOCK_Y = 16;
const int BLOCK_Z = 16;
const int DEPTH = 4;

const float EYE_HEIGHT = 1.5;

// starting position of player
const int START_X = 5;
const int START_Y = 5;
const int START_Z = DEPTH + EYE_HEIGHT;

const float BLOCK_BORDER_WIDTH = 0.03;
const char BLOCK_FILL = '@';
const char BLOCK_BORDER = '.';

class Game {
    public:

        /**
         * Updates player view and position based on keyboard input.
         */
        void updatePlayer();
    

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
         * Fills the existing block map up with blocks.
         * 
         * @pre - the block map must already be initialized.
         */
        void fillMap();

        /**
         * Initializes player position and view area.
         */
        void initPlayer();


};


#endif