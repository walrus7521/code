#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#define WIDTH 800
#define HEIGHT 500
// https://www.geeksforgeeks.org/sdl-library-in-c-c-with-examples/

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error init SDL\n");
    }
    SDL_Window *win = SDL_CreateWindow(
            "GAME",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT, 0);

    uint32_t render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, render_flags);

    SDL_Surface *surface;
    surface = IMG_Load("./wipeout.jpg");

    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);

    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    // adjust height and width of our image box. 
    dest.w /= 6; 
    dest.h /= 6; 

    printf("w: %d, h: %d\n", dest.w, dest.h);

    dest.w = (WIDTH - dest.w)/2;
    dest.h = (HEIGHT - dest.h)/2;

    int close = 0;
    int speed = 300;

    while (!close) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    close = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_W:
                        case SDL_SCANCODE_UP:
                            dest.y -= speed/30;
                            break;
                        case SDL_SCANCODE_A:
                        case SDL_SCANCODE_LEFT:
                            dest.x -= speed/30;
                            break;
                        case SDL_SCANCODE_S:
                        case SDL_SCANCODE_DOWN:
                            dest.y += speed/30;
                            break;
                        case SDL_SCANCODE_D:
                        case SDL_SCANCODE_RIGHT:
                            dest.x += speed/30;
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }
        // right boundary
        if (dest.x + dest.w > WIDTH) {
            dest.x = WIDTH - dest.w;
        }
        // left boundary
        if (dest.x < 0) {
            dest.x = 0;
        }
        // bottom boundary
        if (dest.y + dest.h > HEIGHT) {
            dest.y = HEIGHT - dest.h;
        }
        // upper boundary
        if (dest.y < 0) {
            dest.y = 0;
        }

        // clears the screen
        SDL_RenderClear(rend);
        //SDL_BlitSurface(image, &src, display, &dest);
        SDL_RenderCopy(rend, tex, NULL, &dest);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);

        // calculates the fps
        SDL_Delay(1000/60);

    }

    // destroy texture
    SDL_DestroyTexture(tex);

    // destroy renderer
    SDL_DestroyRenderer(rend);

    // destroy window
    SDL_DestroyWindow(win);

    return 0;
}

