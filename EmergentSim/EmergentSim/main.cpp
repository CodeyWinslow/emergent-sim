#include "GameController.h"
//#include "SDL.h"
//#include "SimDisplay.h"
//#include "Sandbox.h"
//#include <iostream>

//#include "AgentController.h"

//using namespace Agents;

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

    const int numAgents = 5;
    const int sandboxWidth = 20;
    const int sandboxHeight = 20;

    GameController game(numAgents, sandboxWidth, sandboxHeight, windowSettings);
    game.Start();

	return 0;
}