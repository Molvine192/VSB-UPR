#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "dynamic_array.h"
#include <stdlib.h>
#include <time.h>

typedef struct {
    SDL_Rect rect;
    int a,r,g,b;
} Particle;

typedef struct {
    SDL_Rect destinationRect;
    SDL_Texture* image_texture;
    double angle;
} Snowflake;

int S = 5;
int vygeneruj_cislo() {
    int N = S;
    N = (5 * N + 3) % 6323;
    N = (4 * N + 2) % 8127;
    S = N;
    return N;
}

int main()
{

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Snowflakes",
        100,
        100,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_Surface* image_surface = IMG_Load("snowflake.svg");

    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image_surface);
    SDL_FreeSurface(image_surface);

    double angle = 45.0;

    dynarray snowflakes = {};
    dynarray_init(&snowflakes, 2);

    dynarray particles = {};
    dynarray_init(&particles, 2);

    SDL_Event e;
    bool quit = false;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int r_size = vygeneruj_cislo() % 80 + 40;
                    int r_rot = vygeneruj_cislo() % 360;
                    int pos_x = e.button.x-r_size/2;
                    int pos_y = e.button.y-r_size/2;
                    SDL_Rect destinationRect = {pos_x, pos_y, r_size, r_size};
                    Snowflake snowflake = {destinationRect, image_texture, r_rot};
                    Snowflake* p_snowflake = (Snowflake*)malloc(sizeof(Snowflake));
                    *p_snowflake = snowflake;
                    dynarray_push(&snowflakes, (array_type)p_snowflake);
                } 
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        angle += 0.1;

        for (int i = 0; i < particles.size; i++) {
            SDL_Color color = {((Particle*)particles.items[i])->r, ((Particle*)particles.items[i])->g, ((Particle*)particles.items[i])->b, ((Particle*)particles.items[i])->a};
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &((Particle*)particles.items[i])->rect);

            ((Particle*)particles.items[i])->a -= 3;
            if (((Particle*)particles.items[i])->a <= 0) {
                dynarray_remove(&particles, (Particle*)particles.items[i]);
                // printf("Particle deleted\n");
            }
        }

        for (int i = 0; i < snowflakes.size; i++) {
            int r_size = ((Snowflake*)snowflakes.items[i])->destinationRect.w / 14;
            int pos_x = ((Snowflake*)snowflakes.items[i])->destinationRect.x + (vygeneruj_cislo() % (r_size*6) + r_size*4 );
            int pos_y = ((Snowflake*)snowflakes.items[i])->destinationRect.y + (vygeneruj_cislo() % (r_size*2) );
            SDL_Rect rect = {pos_x, pos_y, r_size, r_size};
            Particle particle = {rect, 255, vygeneruj_cislo() % 255, vygeneruj_cislo() % 255, vygeneruj_cislo() % 255};
            Particle* p_particle = (Particle*)malloc(sizeof(Particle));
            *p_particle = particle;
            dynarray_push(&particles, (array_type)p_particle);

            SDL_RenderCopyEx(renderer, ((Snowflake*)snowflakes.items[i])->image_texture, NULL, &((Snowflake*)snowflakes.items[i])->destinationRect, ((Snowflake*)snowflakes.items[i])->angle + angle, NULL, SDL_FLIP_NONE);
            ((Snowflake*)snowflakes.items[i])->destinationRect.y += 1;
            if ( ((Snowflake*)snowflakes.items[i])->destinationRect.y > 600) {
                dynarray_remove(&snowflakes, (Snowflake*)snowflakes.items[i]);
                // printf("Snowflake deleted\n");
            }
        }

        SDL_RenderPresent(renderer);
    }
    
    dynarray_free(&snowflakes);
    dynarray_free(&particles);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}