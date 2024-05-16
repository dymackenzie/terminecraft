## Terminecraft: a terminal-based raytracing Minecraft simulator

![termin_demo](https://github.com/dymackenzie/terminecraft/assets/73260054/24b22578-be55-436b-99c0-bd4fedb47e76)

Terminecraft (Terminal + Minecraft) is a fun little project that I made to learn more about C++ and dabble a bit in raytracing graphics. Since keyboard input is specific to its platform for the terminal,
the program only works on Linux. However, you could technically still use it on Windows or Mac, but you wouldn't be able to move around or place blocks. But hey, at least you'll be able to admire the
terrain generation every time you reset the game.

Use 'q' to quit the game, 'space' to place blocks, 'r' to remove blocks, WASD to move the player around, and the arrow keys to change viewing angle.

### Features:
- Random terrain generation through Perlin noise.
- Raytracing graphics displayed through ASCII characters on the terminal screen.
- Keyboard input through an external framework to allow WASD movement and the ability to place and destroy blocks.
- Thorough unit testing with the Clang2 framework.
- Custom Vector3 classes for raytracing math.
