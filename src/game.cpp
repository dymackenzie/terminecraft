/**
 * @file game.cpp
 */

#include <game.hpp>

/**
 * Default constructor.
 */
Game::Game() {
    initMap();
    fillMap();
    initScreen();
    initPlayer();
}

/**
 * Updates player view and position based on keyboard input.
 */
void Game::updatePlayer() {
    // takes initial position of player
    int posX = (int) player.pos.x;
    int posY = (int) player.pos.y;

    if (block_map[(int) (player.pos.z - EYE_HEIGHT + 0.01)][convertCoordinates(posX, posY)] != ' ') {
        // if block above is not air, move up
        player.pos.z += 1;
    }
    if (block_map[(int) (player.pos.z - EYE_HEIGHT - 0.01)][convertCoordinates(posX, posY)] == ' ') {
        // if block below is air, move down
        player.pos.z -= 1;
    }
    // otherwise, don't change z

    // change view angle
    int c = quick_read();
    if (c == ARROW_UP) {
        player.view.theta += TILT;
    }
    if (c == ARROW_DOWN) {
        player.view.theta -= TILT;
    }
    if (c == ARROW_LEFT) {
        player.view.phi -= TILT;
    }
    if (c == ARROW_RIGHT) {
        player.view.phi += TILT;
    }

    // find direction to move in
    Vector3 playerDirection = VectorS::anglesToVect(player.view);
    // move based on direction
    if (c == 'w') {
        player.pos.x += SPEED * playerDirection.x;
        player.pos.y += SPEED * playerDirection.y;
    }
    if (c == 's') {
        player.pos.x -= SPEED * playerDirection.x;
        player.pos.y -= SPEED * playerDirection.y;
    }
    if (c == 'a') {
        player.pos.x += SPEED * playerDirection.x;
        player.pos.y -= SPEED * playerDirection.y;
    }
    if (c == 'd') {
        player.pos.x -= SPEED * playerDirection.x;
        player.pos.y += SPEED * playerDirection.y;
    }
}

/**
 * If ray is outside bounds of border, return true.
 */
bool Game::isRayOutside(Vector3 v) {
    return (v.x >= CHUNK_X) 
            || (v.y >= CHUNK_Y)
            || (v.z >= CHUNK_Z)
            || (v.x < 0)
            || (v.y < 0)
            || (v.z < 0);
}

/**
 * If vector is within block border size on two axis, return true.
 */
bool Game::onBlockBorder(Vector3 v) {
    int c = 0;
    if (fabsf(v.x - roundf(v.x)) < BLOCK_BORDER_WIDTH) {
        c++;
    }
    if (fabsf(v.y - roundf(v.y)) < BLOCK_BORDER_WIDTH) {
        c++;
    }
    if (fabsf(v.z - roundf(v.z)) < BLOCK_BORDER_WIDTH) {
        c++;
    }
    return c >= 2;
}

/**
 * Initializes initial screen size.
 * 
 * Order: [x][y]
 */
void Game::initScreen() {
    for (int x = 0; x < WIDTH; x++) {
        vector<char> t;
        for (int y = 0; y < HEIGHT; y++) {
            t.push_back(' ');
        }
        screen.push_back(t);
    }
}

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
    for (int z = 0; z < CHUNK_Z; z++) {
        vector<char> v;
        for (int xy = 0; xy < CHUNK_X * CHUNK_Y; xy++) {
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
        for (int xy = 0; xy < CHUNK_X * CHUNK_Y; xy++) {
            block_map[z][xy] = BLOCK_FILL;
        }
    }
}

/**
 * Helper function to convert x and y indices into index for singular array.
 */
int Game::convertCoordinates(int x, int y) {
    return (y * CHUNK_Y) + x;
}