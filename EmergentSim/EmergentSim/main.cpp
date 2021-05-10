#include "GameController.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

int main(int argc, char ** argv)
{
    SimDisplaySettings windowSettings = {
        "Fugma",
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    };

    const int numAgents = 50;
    const int sandboxWidth = 200;
    const int sandboxHeight = 200;

    GameController game(numAgents, sandboxWidth, sandboxHeight, windowSettings);
    game.Start();

	return 0;
}