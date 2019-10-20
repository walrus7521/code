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
void handle_events(){}
void clean(){}
 */

void cleanup(Game *g)
{
    printf("cleanup\n");
    int i;
    for (i = 0; i < 2; i++) {
        SDL_DestroyTexture(g->sprite[i].tex);
        SDL_FreeSurface(g->sprite[i].image);
    }
    SDL_DestroyTexture(g->tex);
    SDL_FreeSurface(g->image);
    SDL_DestroyRenderer(g->rend);

    SDL_CloseAudio();

    SDL_Quit();
}

bool init_sprites(Game *g)
{
    int i;
    for (i = 0; i < 2; i++) {
        g->sprite[i].image = IMG_Load("./boss-meme.jpg");
        if (g->sprite[i].image == NULL) {
            printf("Unable to load sprite bitmap.\n");
            return false;
        }

        g->sprite[i].tex = SDL_CreateTextureFromSurface(g->rend, g->sprite[i].image);
        if (g->sprite[i].tex == NULL) {
            printf("unable to create sprite texture %s\n", SDL_GetError());
            return false;
        }

        SDL_QueryTexture(g->sprite[i].tex, NULL, NULL, &g->sprite[i].dest.w, &g->sprite[i].dest.h);

        g->sprite[i].pos.w = 50; //g->sprite.dest.w;
        g->sprite[i].pos.h = 50; //g->sprite.dest.h;
        g->sprite[i].pos.x = i * 52;
        g->sprite[i].pos.y = i * 52;
    }

    return true;
}

bool init_audio(Game *g)
{
    // https://discourse.libsdl.org/t/playing-wav-file-with-native-sdl2-audio/22251
    SDL_AudioSpec audioSpec;
    SDL_zero(audioSpec);
    audioSpec.channels = 2;
    audioSpec.freq     = 44100;
    audioSpec.format   = AUDIO_S16;
    audioSpec.userdata = NULL; //(void*)myDataLocation;
    audioSpec.callback = NULL; //MyAudioCallback;

    SDL_AudioSpec wav_spec;
    if (SDL_LoadWAV("./Boom-Kick.wav", &wav_spec, &g->wav_buffer, &g->wav_length)) {
 
        printf("audio len: %d\n", g->wav_length);
        g->audioDevice = SDL_OpenAudioDevice(NULL, 0, &audioSpec, 
                &audioSpec, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
        // actually start playback
        if (g->audioDevice) {
            SDL_PauseAudioDevice(g->audioDevice, 0);
        }
    }
    return true;
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

    g->delay = MILLISECONDS_DELAY; // milliseconds
    g->update_rate = 10;
    g->speed = 100;
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
    //const SDL_Point center = {dest.w/2, dest.h/2};
    //const double rot_angle = 0; //45;
    //SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
    //SDL_RenderCopyEx(rend, tex, &src, &dest, rot_angle, &center, flip);        
    SDL_RenderCopy(g->rend, g->tex, NULL, NULL);
    //SDL_RenderCopyEx(g->rend, g->tex, NULL, NULL, 0, NULL, 0);

    // triggers the double buffers
    // for multiple rendering
    //SDL_RenderPresent(g->rend);
        
#endif
    return true;
}

bool render_sprites(Game *g)
{
    int i;
    for (i = 0; i < 2; i++) {
    //const double rot_angle = 0;
    //SDL_RenderCopy(g->rend, g->sprite.tex, &g->sprite.src, &g->sprite.dest, 
    //      rot_angle, &center, flip);        
        SDL_RenderCopy(g->rend, g->sprite[i].tex, NULL, &g->sprite[i].pos); //&g->sprite.dest);
    }
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
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_W:
                    case SDL_SCANCODE_UP:
                        g->dest.y -= g->speed/30;
                        break;
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        g->dest.x -= g->speed/30;
                        break;
                    case SDL_SCANCODE_S:
                    case SDL_SCANCODE_DOWN:
                        g->dest.y += g->speed/30;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        g->dest.x += g->speed/30;
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        g->close = true;
                        break;

                    default:
                        break;
                }
            default:
                break;
        }
    }
    return true;
}

bool update(Game *g)
{
    int i;
    static int frame = 0;
    if (frame % g->update_rate == 0) {
        SDL_QueueAudio(g->audioDevice, g->wav_buffer, g->wav_length/10);
        for (i = 0; i < 2; i++) {
            g->sprite[i].pos.x += g->speed/30;
            g->sprite[i].pos.y += g->speed/30;
        }
    }
    frame++;
    SDL_RenderPresent(g->rend);
    return true;
}

int main()
{
    Game *g = malloc(sizeof(Game));
    memset(g, 0, sizeof(Game));

    if (!init(g)) {
        printf("failed init\n");
        return 1;
    }
    if (!init_audio(g)) {
        printf("failed init audio\n");
        return 1;
    }
    if (!init_sprites(g)) {
        printf("failed init sprite\n");
        return 1;
    }
    while (!g->close) {

        render(g);
        render_sprites(g);
 
        update(g);
        handle_events(g);

        /* Pause as the viewer gasps in awe. */
        SDL_Delay(g->delay);
    }

    cleanup(g);
    printf("Success!\n");
    
    return 0;
}


