#include <SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<stdio.h>
#include"init.h"

void ending_program(Variables* v)
{

    TTF_CloseFont(v -> resources.font);
    TTF_Quit();

    SDL_DestroyRenderer(v -> app.renderer);
    SDL_DestroyWindow(v -> app.window);

    SDL_Quit();
}