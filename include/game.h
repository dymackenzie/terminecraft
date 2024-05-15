/**
 * @file game.h
 */

#ifndef GAME_H
#define GAME_H

#include <vec3.h>
#include <vecs.h>

const int WIDTH = 500;
const int HEIGHT = 180;

const int VIEW_WIDTH = 1; // in radians
const int VIEW_HEIGHT = 0.7; // in radians

const int BLOCK_X = 20;
const int BLOCK_Y = 20;
const int BLOCK_Z = 10;

const float EYE_HEIGHT = 1.5;

// starting position of player
const int START_X = 5;
const int START_Y = 5;
const int START_Z = 4 + EYE_HEIGHT;

const float BLOCK_BORDER_WIDTH = 0.03;
const char BLOCK_FILL = '@';
const char BLOCK_BORDER = '.';

class Game {
    public:
        // struct for player attributes
        struct Player {
            Vector3 pos;
            VectorS view;
        } player;




    private:

        


};


#endif