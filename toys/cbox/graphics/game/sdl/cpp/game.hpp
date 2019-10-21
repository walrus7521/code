#ifndef __GAME_H__
#define __GAME_H__

#define WIDTH  640
#define HEIGHT 480
#define MILLISECONDS_DELAY 100


typedef class _Sprite {
  public:
    SDL_Surface *image;
    SDL_Renderer *rend;
    SDL_Texture *tex;
    SDL_Rect src, dest;
    SDL_Rect pos;
 } Sprite;

typedef class Game {
  public:
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

    void cleanup() {
        printf("cleanup\n");
        int i;
        for (i = 0; i < 2; i++) {
            SDL_DestroyTexture(this->sprite[i].tex);
            SDL_FreeSurface(this->sprite[i].image);
        }
        SDL_DestroyTexture(this->tex);
        SDL_FreeSurface(this->image);
        SDL_DestroyRenderer(this->rend);
        SDL_CloseAudio();
        SDL_Quit();
    }

    bool init_sprites()
    {
        int i;
        for (i = 0; i < 2; i++) {
            this->sprite[i].image = IMG_Load("./boss-meme.jpg");
            if (this->sprite[i].image == NULL) {
                printf("Unable to load sprite bitmap.\n");
                return false;
            }

            this->sprite[i].tex = SDL_CreateTextureFromSurface(this->rend, this->sprite[i].image);
            if (this->sprite[i].tex == NULL) {
            printf("unable to create sprite texture %s\n", SDL_GetError());
            return false;
            }

            SDL_QueryTexture(this->sprite[i].tex, NULL, NULL, &this->sprite[i].dest.w, &this->sprite[i].dest.h);

            this->sprite[i].pos.w = 50; //this->sprite.dest.w;
            this->sprite[i].pos.h = 50; //this->sprite.dest.h;
            this->sprite[i].pos.x = i * 52;
            this->sprite[i].pos.y = i * 52;
        }
        return true;
    }

    bool init_audio()
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
        if (SDL_LoadWAV("./Boom-Kick.wav", &wav_spec, &this->wav_buffer, &this->wav_length)) {
 
            printf("audio len: %d\n", this->wav_length);
            this->audioDevice = SDL_OpenAudioDevice(NULL, 0, &audioSpec, 
                &audioSpec, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE);
            // actually start playback
            if (this->audioDevice) {
                SDL_PauseAudioDevice(this->audioDevice, 0);
            }
        }
        return true;
    }

    bool init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            printf("error init SDL\n");
            return false;
        }

        this->window = SDL_CreateWindow("intro", SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
        if (this->window == NULL) {
            printf("unable to create window %s\n", SDL_GetError());
            return false;
        }

        if (SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP)) {
            printf("unable to set fullscreen %s\n", SDL_GetError());
            return false;
        }

        this->rend = SDL_CreateRenderer(this->window, -1, 
            /*SDL_RENDERER_ACCELERATED |*/ SDL_RENDERER_SOFTWARE);
        if (this->rend == NULL) {
            printf("unable to create renderer %s\n", SDL_GetError());
            return false;
        }
    
        this->image = IMG_Load("./wipeout.jpg");
        if (this->image == NULL) {
            printf("Unable to load bitmap.\n");
            return false;
        }

        this->tex = SDL_CreateTextureFromSurface(this->rend, this->image);
        if (this->tex == NULL) {
            printf("unable to create texture %s\n", SDL_GetError());
            return false;
        }

        SDL_QueryTexture(this->tex, NULL, NULL, &this->dest.w, &this->dest.h);

        // adjust height and width of our image box. 
        this->dest.w /= 6; this->dest.h /= 6; 

        printf("w: %d, h: %d\n", this->dest.w, this->dest.h);

        this->dest.w = (WIDTH - this->dest.w)/2;
        this->dest.h = (HEIGHT - this->dest.h)/2;

        this->screen = SDL_GetWindowSurface(this->window);
        if (this->screen == NULL) {
            printf("unable to get surface %s\n", SDL_GetError());
            return false;
        }

        this->delay = MILLISECONDS_DELAY; // milliseconds
        this->update_rate = 10;
        this->speed = 100;
        this->close = false;
        return true;
    }

    bool render()
    {
        // clear the screen
        SDL_RenderClear(this->rend);

    #define DO_BLT (0)
    #if DO_BLT
        this->src.x = 0;
        this->src.y = 0;
        this->src.w = this->image->w; /* copy the entire image */
        this->src.h = this->image->h;
        this->dest.x = 0;
        this->dest.y = 0;
        this->dest.w = this->image->w;
        this->dest.h = this->image->h;
        
        /* Draw the bitmap to the screen. We are using a hicolor video
            mode, so we don't have to worry about colormap silliness.
            It is not necessary to lock surfaces before blitting; SDL
           will handle that. */
        //SDL_BlitSurface(image, &src, screen, &dest);

        // last parameter stretches image to entire screen if NULL
        SDL_BlitScaled(this->image, &this->src, this->screen, NULL); //&dest);

        // this flickers the screen
        if (SDL_UpdateWindowSurface(this->window)) {
            printf("unable to update surface %s\n", SDL_GetError());
            return false;
        }
    #else
        //const SDL_Point center = {dest.w/2, dest.h/2};
        //const double rot_angle = 0; //45;
        //SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
        //SDL_RenderCopyEx(rend, tex, &src, &dest, rot_angle, &center, flip);        
        SDL_RenderCopy(this->rend, this->tex, NULL, NULL);
        //SDL_RenderCopyEx(this->rend, this->tex, NULL, NULL, 0, NULL, 0);
    #endif
        return true;
    }

    bool render_sprites()
    {
        int i;
        for (i = 0; i < 2; i++) {
        //const double rot_angle = 0;
        //SDL_RenderCopy(this->rend, this->sprite.tex, &this->sprite.src, &this->sprite.dest, 
        //      rot_angle, &center, flip);        
            SDL_RenderCopy(this->rend, this->sprite[i].tex, NULL, &this->sprite[i].pos); //&this->sprite.dest);
        }
        return true;
    }

    bool handle_events()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    this->close = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            this->dest.y -= this->speed/30;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            this->dest.x -= this->speed/30;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            this->dest.y += this->speed/30;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            this->dest.x += this->speed/30;
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            this->close = true;
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

    bool update()
    {
        int i;
        static int frame = 0;
        if (frame % this->update_rate == 0) {
            SDL_QueueAudio(this->audioDevice, this->wav_buffer, this->wav_length/10);
            for (i = 0; i < 2; i++) {
                this->sprite[i].pos.x += this->speed/30;
                this->sprite[i].pos.y += this->speed/30;
            }
        }
        frame++;
        SDL_RenderPresent(this->rend);
        return true;
    }

} Game;

#endif // __GAME_H__
