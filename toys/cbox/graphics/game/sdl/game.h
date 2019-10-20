#ifndef __GAME_H__
#define __GAME_H__

typedef struct _Sprite {
    SDL_Surface *image;
    SDL_Renderer *rend;
    SDL_Texture *tex;
    SDL_Rect src, dest;
    SDL_Rect pos;
 } Sprite;

typedef struct _Game {
    SDL_Surface *screen;
    SDL_Window *window;
    SDL_Surface *image;
    SDL_Renderer *rend;
    SDL_Texture *tex;
    SDL_AudioDeviceID audioDevice;
    SDL_Rect src, dest;
    Sprite sprite[2];
    uint32_t wav_length;
    uint8_t *wav_buffer;
    int delay;
    int speed;
    int update_rate;
    bool close;
} Game;

bool init(Game *g);
bool init_sprites(Game *g);
bool render(Game *g);
bool render_sprites(Game *g);
bool update(Game *g);
bool handle_events(Game *g);
void cleanup(Game *g);

#endif // __GAME_H__
