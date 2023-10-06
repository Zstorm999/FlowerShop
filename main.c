#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main()
{

    // initialize the library;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialized: %s\n", SDL_GetError());
        exit(-1);
    }

    // create the window
    SDL_Window *window = SDL_CreateWindow("Flower Shop", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created: %s\n", SDL_GetError());
        exit(-1);
    }

    // create surface
    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

    // fill surface with white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    // apply changes
    SDL_UpdateWindowSurface(window);

    // main loop : stay open while window is not closed
    SDL_Event e;
    SDL_bool quit = SDL_FALSE;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = SDL_TRUE;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}