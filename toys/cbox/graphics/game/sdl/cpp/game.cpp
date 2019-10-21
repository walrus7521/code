#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"

int main()
{
    Game *g = new(Game); //(Game *) malloc(sizeof(Game));
    memset(g, 0, sizeof(Game));

    if (!g->init()) {
        printf("failed init\n");
        return 1;
    }
    if (!g->init_audio()) {
        printf("failed init audio\n");
        return 1;
    }
    if (!g->init_sprites()) {
        printf("failed init sprite\n");
        return 1;
    }
    while (!g->close) {

        g->render();
        g->render_sprites();
 
        g->update();
        g->handle_events();

        /* Pause as the viewer gasps in awe. */
        SDL_Delay(g->delay);
    }

    g->cleanup();
    printf("Success!\n");
    
    return 0;
}


