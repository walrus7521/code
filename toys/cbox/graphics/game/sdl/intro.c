#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"

#define WIDTH  640
#define HEIGHT 480
#define MILLISECONDS_DELAY 100

/*

void init() { m_bRunning = true; }
void render(){}
void update(){}
void handleEvents(){}
void clean(){}

 */

void cleanup(Game *g)
{
    printf("cleanup\n");

    // destroy texture
    SDL_DestroyTexture(g->tex);

    // destroy renderer
    SDL_DestroyRenderer(g->rend);
    
    SDL_FreeSurface(g->image);

    SDL_Quit();
}

bool init(Game *g)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error init SDL\n");
        return false;
    }

    g->window = SDL_CreateWindow("intro", SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (g->window == NULL) {
        printf("unable to create window %s\n", SDL_GetError());
        return false;
    }

    if (SDL_SetWindowFullscreen(g->window, SDL_WINDOW_FULLSCREEN_DESKTOP)) {
        printf("unable to set fullscreen %s\n", SDL_GetError());
        return false;
    }

    g->rend = SDL_CreateRenderer(g->window, -1, 
            /*SDL_RENDERER_ACCELERATED |*/ SDL_RENDERER_SOFTWARE);
    if (g->rend == NULL) {
        printf("unable to create renderer %s\n", SDL_GetError());
        return false;
    }
    
    g->image = IMG_Load("./wipeout.jpg");
    if (g->image == NULL) {
        printf("Unable to load bitmap.\n");
        return false;
    }

    g->tex = SDL_CreateTextureFromSurface(g->rend, g->image);
    if (g->tex == NULL) {
        printf("unable to create texture %s\n", SDL_GetError());
        return false;
    }

    SDL_QueryTexture(g->tex, NULL, NULL, &g->dest.w, &g->dest.h);

    // adjust height and width of our image box. 
    g->dest.w /= 6; g->dest.h /= 6; 

    printf("w: %d, h: %d\n", g->dest.w, g->dest.h);

    g->dest.w = (WIDTH - g->dest.w)/2;
    g->dest.h = (HEIGHT - g->dest.h)/2;

    g->screen = SDL_GetWindowSurface(g->window);
    if (g->screen == NULL) {
        printf("unable to get surface %s\n", SDL_GetError());
        return false;
    }

    g->close = false;
    return true;
}

bool render(Game *g)
{
    // clear the screen
    SDL_RenderClear(g->rend);

#define DO_BLT (0)
#if DO_BLT
    g->src.x = 0;
    g->src.y = 0;
    g->src.w = g->image->w; /* copy the entire image */
    g->src.h = g->image->h;
    g->dest.x = 0;
    g->dest.y = 0;
    g->dest.w = g->image->w;
    g->dest.h = g->image->h;
        
    g->delay = MILLISECONDS_DELAY; // milliseconds
    /* Draw the bitmap to the screen. We are using a hicolor video
       mode, so we don't have to worry about colormap silliness.
       It is not necessary to lock surfaces before blitting; SDL
       will handle that. */
    //SDL_BlitSurface(image, &src, screen, &dest);

    // last parameter stretches image to entire screen if NULL
    SDL_BlitScaled(g->image, &g->src, g->screen, NULL); //&dest);

    // this flickers the screen
    if (SDL_UpdateWindowSurface(g->window)) {
        printf("unable to update surface %s\n", SDL_GetError());
        return false;
    }
#else
    g->delay = 100; //0/60;
    //const SDL_Point center = {dest.w/2, dest.h/2};
    //const double rot_angle = 0; //45;
    //SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
    //SDL_RenderCopyEx(rend, tex, &src, &dest, rot_angle, &center, flip);        
    SDL_RenderCopyEx(g->rend, g->tex, NULL, NULL, 0, NULL, 0); //SDL_FLIP_VERTICAL);

    // triggers the double buffers
    // for multiple rendering
    SDL_RenderPresent(g->rend);
        
#endif
    return true;
}

bool handle_events(Game *g)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                g->close = true;
                break;
            default:
                break;
        }
    }
    return true;
}

bool update(Game *g)
{
    return true;
}

int main()
{
    Game *g = malloc(sizeof(Game));
    memset(g, 0, sizeof(Game));

    if (!init(g)) {
        return 1;
    }

    while (!g->close) {

        render(g);
        update(g);
        handle_events(g);

        /* Pause as the viewer gasps in awe. */
        SDL_Delay(g->delay);
    }

    cleanup(g);
    printf("Success!\n");
    
    return 0;
}


