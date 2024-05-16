/**
 * @file game.cpp
 */

#include <game.hpp>

/**
 * Bailout function to stop leaving terminal in a bad state.
 */
void bailout() {
    set_mouse_mode(false);
    set_raw_mode(false);
}

/**
 * Runs all necessary game logic.
 */
void Game::run()
{
    atexit(bailout);
    set_raw_mode(true);
    while (true)
    {
        int c = quick_read();
        // quit
        if (c == 'q') {
            set_raw_mode(false);
            break;
        }
        if (c == ERR) usleep(10'000);

        // updates position of player
        updatePlayer(c); 

        // handle block highlight and placement
        Vector3 currBlock = getBlock();
        bool hasBlock = !isRayOutside(currBlock);
        bool wasRemoved = false;
        if (hasBlock)
        {
            block_map[(int)currBlock.z][convertCoordinates((int)currBlock.x, (int)currBlock.y)] = BLOCK_HIGHLIGHT;
            if (c == 'r')
            {
                block_map[(int)currBlock.z][convertCoordinates((int)currBlock.x, (int)currBlock.y)] = ' ';
                wasRemoved = true;
            }
            else if (c == ' ')
            {
                placeBlock(currBlock);
            }
        }

        // render picture
        refreshScreen();

        // draw picture
        drawScreen();

        // reset block highlight if it wasn't removed
        if (hasBlock && !wasRemoved)
        {
            block_map[(int)currBlock.z][convertCoordinates((int)currBlock.x, (int)currBlock.y)] = BLOCK_FILL;
        }
    }
}

/**
 * Updates player view and position based on keyboard input.
 * 
 * @param c - input keyboard
 */
void Game::updatePlayer(int c)
{
    // takes initial position of player
    int posX = (int)player.pos.x;
    int posY = (int)player.pos.y;

    if (block_map[(int)(player.pos.z - EYE_HEIGHT + 0.01)][convertCoordinates(posX, posY)] != ' ')
    {
        // if block above is not air, move up
        player.pos.z += 1;
    }
    if (block_map[(int)(player.pos.z - EYE_HEIGHT - 0.01)][convertCoordinates(posX, posY)] == ' ')
    {
        // if block below is air, move down
        player.pos.z -= 1;
    }
    // otherwise, don't change z

    // change view angle
    if (c == ARROW_UP)
    {
        player.view.theta += TILT;
    }
    if (c == ARROW_DOWN)
    {
        player.view.theta -= TILT;
    }
    if (c == ARROW_LEFT)
    {
        player.view.phi -= TILT;
    }
    if (c == ARROW_RIGHT)
    {
        player.view.phi += TILT;
    }

    // find direction to move in
    Vector3 playerDirection = VectorS::anglesToVect(player.view);
    // move based on direction
    if (c == 'w')
    {
        player.pos.x += SPEED * playerDirection.x;
        player.pos.y += SPEED * playerDirection.y;
    }
    if (c == 's')
    {
        player.pos.x -= SPEED * playerDirection.x;
        player.pos.y -= SPEED * playerDirection.y;
    }
    if (c == 'a')
    {
        player.pos.x += SPEED * playerDirection.y;
        player.pos.y -= SPEED * playerDirection.x;
    }
    if (c == 'd')
    {
        player.pos.x -= SPEED * playerDirection.y;
        player.pos.y += SPEED * playerDirection.x;
    }
}

/**
 * If ray is outside bounds of border, return true.
 */
bool Game::isRayOutside(Vector3 v)
{
    return (v.x >= CHUNK_X) || (v.y >= CHUNK_Y) || (v.z >= CHUNK_Z) || (v.x < 0) || (v.y < 0) || (v.z < 0);
}

/**
 * If vector is within block border size on two axis, return true.
 */
bool Game::onBlockBorder(Vector3 v)
{
    int c = 0;
    if (fabsf(v.x - roundf(v.x)) < BLOCK_BORDER_WIDTH)
    {
        c++;
    }
    if (fabsf(v.y - roundf(v.y)) < BLOCK_BORDER_WIDTH)
    {
        c++;
    }
    if (fabsf(v.z - roundf(v.z)) < BLOCK_BORDER_WIDTH)
    {
        c++;
    }
    return c >= 2;
}

/**
 * Generates picture by raytracing for each element on screen data structure.
 */
void Game::refreshScreen()
{
    // initializes initial ray tracing directions
    vector<vector<Vector3>> dirs = initDir();
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            screen[x][y] = raytracing(dirs[x][y]);
            // raytraces each inidivudal pixel given its initial direction.
        }
    }
}

/**
 * Prints out screen onto terminal.
 */
void Game::drawScreen()
{
    printf("\033[0;0H"); // this jumps to (0, 0) to overwrite the current picture
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            printf("%c", screen[x][y]);
        }
        printf("\n");
    }
}

/**
 * Initializes the initial ray tracing directions for each pixel on screen
 */
vector<vector<Vector3>> Game::initDir()
{
    // initialize initial direction array
    vector<vector<Vector3>> dirs;

    // finds middle of screen in vector form
    VectorS t = player.view;

    // boundaries of the frame
    Vector3 bottom = VectorS::anglesToVect(VectorS::add(t, VectorS(0, -VIEW_HEIGHT / 2.0)));
    Vector3 top = VectorS::anglesToVect(VectorS::add(t, VectorS(0, VIEW_HEIGHT / 2.0)));
    Vector3 right = VectorS::anglesToVect(VectorS::add(t, VectorS(VIEW_WIDTH / 2.0, 0)));
    Vector3 left = VectorS::anglesToVect(VectorS::add(t, VectorS(-VIEW_WIDTH / 2.0, 0)));

    // middle of frame
    Vector3 vertical_mid = Vector3::scale(Vector3::add(top, bottom), 0.5);
    Vector3 horizontal_mid = Vector3::scale(Vector3::add(right, left), 0.5);

    // from middle of frame to boundaries
    Vector3 middle_point_left = Vector3::sub(left, horizontal_mid);
    Vector3 middle_point_top = Vector3::sub(top, vertical_mid);

    // populates the array
    // what this does is it takes the initial point of (0, 0) and has as vector
    // pointing to it. Then, it scales the vectors pointing from the middle of the
    // screen to the left and top and adds it on to the initial vector point of (0, 0).
    // the initial vector is now pointing from the camera to the next pixel on screen.
    // this allows us to calculate every ray direction from a singular point (namely our
    // camera) onto the screen at a given distance.
    for (int x = 0; x < WIDTH; x++)
    {
        vector<Vector3> t_array;
        for (int y = 0; y < HEIGHT; y++)
        {
            Vector3 d = Vector3::add(horizontal_mid, Vector3::add(middle_point_left, middle_point_top));
            float x_scale = ((float)x / (WIDTH - 1)) * 2;
            float y_scale = ((float)y / (HEIGHT - 1)) * 2;
            d = Vector3::sub(d, Vector3::scale(middle_point_left, x_scale));
            d = Vector3::sub(d, Vector3::scale(middle_point_top, y_scale));
            d = Vector3::normalize(d); // normalizes to make length 1
            t_array.push_back(d);
        }
        dirs.push_back(t_array);
    }

    return dirs;
}

/**
 * Raytraces from given initial direction until it hits a block.
 */
char Game::raytracing(Vector3 dir)
{
    Vector3 position = player.pos; // position to raytrace from
    while (!isRayOutside(position))
    {
        // while ray is within bounds, check char
        // and returns first non-null character if finds
        char block = block_map[(int)position.z][convertCoordinates((int)position.x, (int)position.y)];
        if (block != ' ')
        { // if not empty
            // check if it's on border
            if (onBlockBorder(position))
                return BLOCK_BORDER;
            else
                return block;
        }

        // increments raytracer position and repeats the process
        position = Vector3::add(position, Vector3::scale(dir, raytraceIncrement(position, dir) + 0.01));
    }

    return ' ';
}

/**
 * Get block player is pointing at,
 * basically like raytracing except for the middle ray and
 * the function returns position of the block player is pointing at
 */
Vector3 Game::getBlock()
{
    Vector3 position = player.pos;                    // position to raytrace from
    Vector3 dir = VectorS::anglesToVect(player.view); // get middle ray in the direction player is facing
    while (!isRayOutside(position))
    {
        // while ray is within bounds, check char
        // and returns when reaches a block
        char block = block_map[(int)position.z][convertCoordinates((int)position.x, (int)position.y)];
        if (block != ' ')
        { // if not empty
            return position;
        }
        // increments raytracer position and repeats the process
        position = Vector3::add(position, Vector3::scale(dir, raytraceIncrement(position, dir) + 0.01));
    }

    return position;
}

/**
 * Place a block on the face the player is pointing at, it does this
 * by finding the closest face the player is pointing at and then
 * places block in respective location.
 * Block faces 0-5: x+, x-, y+, y-, z+, z-
 */
void Game::placeBlock(Vector3 curr)
{
    // puts distances to faces of block in array and finds minimum
    vector<float> distances = {
        fabsf(((int)curr.x + 1) - curr.x),
        fabsf(((int)curr.x) - curr.x),
        fabsf(((int)curr.y + 1) - curr.y),
        fabsf(((int)curr.y) - curr.y),
        fabsf(((int)curr.z + 1) - curr.z),
        fabsf(((int)curr.z) - curr.z)};

    // finds minimum index
    int minimumIndex = distance(begin(distances), min_element(begin(distances), end(distances)));

    Vector3 pos = Vector3((int)curr.x, (int)curr.y, (int)curr.z);

    // places block based on closest face
    if (minimumIndex == 0)
    {
        // x+
        block_map[pos.z][convertCoordinates(pos.x + 1, pos.y)] = BLOCK_FILL;
    }
    else if (minimumIndex == 1)
    {
        // x-
        block_map[pos.z][convertCoordinates(pos.x - 1, pos.y)] = BLOCK_FILL;
    }
    else if (minimumIndex == 2)
    {
        // y+
        block_map[pos.z][convertCoordinates(pos.x, pos.y + 1)] = BLOCK_FILL;
    }
    else if (minimumIndex == 3)
    {
        // y-
        block_map[pos.z][convertCoordinates(pos.x, pos.y - 1)] = BLOCK_FILL;
    }
    else if (minimumIndex == 4)
    {
        // z+
        block_map[pos.z + 1][convertCoordinates(pos.x, pos.y)] = BLOCK_FILL;
    }
    else
    {
        // z-
        block_map[pos.z - 1][convertCoordinates(pos.x, pos.y)] = BLOCK_FILL;
    }
}

/**
 * Initializes initial screen size.
 *
 * Order: [x][y]
 */
void Game::initScreen()
{
    for (int x = 0; x < WIDTH; x++)
    {
        vector<char> t;
        for (int y = 0; y < HEIGHT; y++)
        {
            t.push_back(' ');
        }
        screen.push_back(t);
    }
}

/**
 * Initializes player position and view area.
 */
void Game::initPlayer()
{
    player.pos = Vector3(START_X, START_Y, START_Z);
    player.view = VectorS(0, 0);
}

/**
 * Initializes initial block map.
 */
void Game::initMap()
{
    // fills whole map with empty blocks
    for (int z = 0; z < CHUNK_Z; z++)
    {
        vector<char> v;
        for (int xy = 0; xy < CHUNK_X * CHUNK_Y; xy++)
        {
            v.push_back(' ');
        }
        block_map.push_back(v);
    }
}

/**
 * Fills the existing block map up with blocks.
 * Includes perlin noise for terrain generation.
 *
 * @pre - the block map must already be initialized.
 */
void Game::fillMap()
{
    for (int x = 0; x < CHUNK_X; x++)
    {
        for (int y = 0; y < CHUNK_Y; y++)
        {
            auto noise = 0;
            if (isRandom)
                noise = db::perlin(double(x) / 12.0, double(y) / 12.0) * 4 * DEPTH + DEPTH;
            for (int z = 0; z < max(DEPTH, (int)noise); z++) {
                block_map[z][convertCoordinates(x, y)] = BLOCK_FILL;
            }
        }
    }
}

/**
 * Helper function to both calculate how much to increment raytrace by, keeping it
 * clamped to 2 or below.
 *
 * @param position - given position of raytrace
 * @param dir - given direction of raytrace
 */
float Game::raytraceIncrement(Vector3 position, Vector3 dir)
{
    float eps = 0.01;
    float ray_increment = 2; // starting value
    // stops incremenet from increasing by greater than 2
    // x axis
    if (dir.x > eps)
    {
        ray_increment = min(ray_increment, ((int)(position.x + 1) - position.x) / dir.x);
    }
    else if (dir.x < -eps)
    {
        ray_increment = min(ray_increment, ((int)(position.x) - position.x) / dir.x);
    }

    // y axis
    if (dir.y > eps)
    {
        ray_increment = min(ray_increment, ((int)(position.y + 1) - position.y) / dir.y);
    }
    else if (dir.y < -eps)
    {
        ray_increment = min(ray_increment, ((int)(position.y) - position.y) / dir.y);
    }

    // z axis
    if (dir.z > eps)
    {
        ray_increment = min(ray_increment, ((int)(position.z + 1) - position.z) / dir.z);
    }
    else if (dir.z < -eps)
    {
        ray_increment = min(ray_increment, ((int)(position.z) - position.z) / dir.z);
    }

    return ray_increment;
}

/**
 * Helper function to convert x and y indices into index for singular array.
 */
int Game::convertCoordinates(int x, int y)
{
    return (y * CHUNK_Y) + x;
}