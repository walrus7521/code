#include <stdio.h>
#include <SDL2/SDL.h>

int main()
{
    SDL_Surface *screen;
    SDL_Window *window = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("error init SDL\n");
        return 1;
    }
    
    atexit(SDL_Quit);

    window = SDL_CreateWindow("intro", SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    if (window == NULL) {
        printf("unable to create window %s\n", SDL_GetError());
        return 1;
    }

    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        printf("unable to get surface %s\n", SDL_GetError());
        return 1;
    }
    
    printf("Success!\n");
    
    return 0;
}

