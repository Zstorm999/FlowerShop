#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// all of these are constants in case we need to change them we only need to change one
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int IMAGE_WIDTH = 150;
const int IMAGE_HEIGHT = 150;

int main()
{

    // initialize the library;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialized: %s\n", SDL_GetError());
        exit(-1);
    }

    // create the window
    SDL_Window *window = SDL_CreateWindow(
        "Flower Shop", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        // the bar basically means "and" for the bitflags

    if (window == NULL)
    {
        printf("Window could not be created: %s\n", SDL_GetError());
        exit(-1);
    }

    // create surface
    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

    // fill surface with white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    // pos x posy width height
    // {x,y,...} these are struct (we'll see them later in class) 
    SDL_Rect sprite_destination = {20, 20, IMAGE_WIDTH, IMAGE_HEIGHT};
    SDL_Rect sprite_source = {0, 0, IMAGE_WIDTH, IMAGE_HEIGHT};

    // all images must be in bmp format
    SDL_Surface *sprite_pnt = SDL_LoadBMP("assets/In-Game Sprite/fleur-ronde-rose.bmp");
    if (sprite_pnt == NULL)
    {
        printf("Sprite could not be loaded: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    // creates a texture from an image to add it on the renderer.
    // the renderer allows us to use functions such as SDL_RenderDrawLine
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, sprite_pnt);
    SDL_FreeSurface(sprite_pnt);

    int position = 0;
    Uint32 lastTick = 0;
    Uint32 currentTick = 0; 

    // main loop : stay open while window is not closed
    SDL_Event e;
    SDL_bool quit = SDL_FALSE;
    while (!quit)
    {
        lastTick = SDL_GetTicks();
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = SDL_TRUE;
        }

        position++;
        if (position > 350){
            position = 0;
        }
        
        sprite_destination.x = position;

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        SDL_RenderDrawLine(renderer,20,20,80,20);
        SDL_RenderCopy(renderer, texture,&sprite_source,&sprite_destination);

        // apply changes
        SDL_UpdateWindowSurface(window);
        SDL_RenderPresent(renderer);

        currentTick = SDL_GetTicks();
        SDL_Delay((1000/60)-currentTick+lastTick);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}