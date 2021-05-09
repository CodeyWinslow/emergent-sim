//#include "SDL.h"
#include "SimDisplay.h"
#include "Sandbox.h"
#include <stdio.h>
#include <iostream>
using std::cout;
using std::cin;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char ** argv)
{
    Sandbox sb(100,100);
    SimDisplay display(sb,"Fugma", 800, 600);
    /*for (int ii = 0; ii < 480; ++ii)
    {
        display.Update();
    }*/

    while (display.Update());

    ////The window we'll be rendering to
    //SDL_Window* window = NULL;

    ////The surface contained by the window
    //SDL_Surface* screenSurface = NULL;

    ////Initialize SDL
    //if (SDL_Init(SDL_INIT_VIDEO) < 0)
    //{
    //    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    //    return 1;
    //}

    ////Create window
    //window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //if (window == NULL)
    //{
    //    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    //}
    //else
    //{
    //    //Get window surface
    //    screenSurface = SDL_GetWindowSurface(window);

    //    //Fill the surface white
    //    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    //    //Update the surface
    //    SDL_UpdateWindowSurface(window);

    //    //Wait two seconds
    //    SDL_Delay(2000);
    //}

    //SDL_DestroyWindow(window);

    ////Quit SDL subsystems
    //SDL_Quit();

	return 0;
}