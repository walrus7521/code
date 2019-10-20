#ifndef __GAME_H__
#define __GAME_H__


typedef struct _Game {
    SDL_Surface *screen;
    SDL_Window *window;
    SDL_Surface *image;
    SDL_Renderer *rend;
    SDL_Texture *tex;
    SDL_Rect src, dest;
    int delay;
    bool close;
} Game;

bool init(Game *g);
bool render(Game *g);
bool update(Game *g);
bool handle_events(Game *g);
void cleanup(Game *g);

#endif // __GAME_H__
