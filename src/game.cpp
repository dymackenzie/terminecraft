/**
 * @file game.cpp
 */

#include <game.hpp>

/**
 * Initializes player position and view area.
 */
void Game::initPlayer() {
    player.pos = Vector3(START_X, START_Y, START_Z);
    player.view = VectorS(0, 0);
}

/**
 * Initializes initial block map.
 */
void Game::initMap() {
    // fills whole map with empty blocks
    for (int z = 0; z < BLOCK_Z; z++) {
        vector<char> v;
        for (int xy = 0; xy < BLOCK_X * BLOCK_Y; xy++) {
            v.push_back(' ');
        }
        block_map.push_back(v);
    }
}

/**
 * Fills the existing block map up with blocks.
 * 
 * @pre - the block map must already be initialized.
 */
void Game::fillMap() {
    for (int z = 0; z < DEPTH; z++) {
        // z-slice
        for (int xy = 0; xy < BLOCK_X * BLOCK_Y; xy++) {
            block_map[z][xy] = BLOCK_FILL;
        }
    }
}

