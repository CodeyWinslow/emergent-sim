#include "GameController.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

int main(int argc, char ** argv)
{
    SimDisplaySettings windowSettings = {
        "Fugma",
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        {200, 192, 181, 255},
        {214, 115, 13, 255},
        {13, 214, 78, 255},
        {13, 137, 214, 255}
    };

    const int numAgents = 100;
    const int sandboxWidth = 100;
    const int sandboxHeight = 100;

    GameController game(numAgents, 5, sandboxWidth, sandboxHeight, windowSettings);
    game.Start();

	return 0;
}