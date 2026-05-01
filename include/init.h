#ifndef INIT_H
#define INIT_H

#include <SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>

typedef struct 
{
    bool running;

    SDL_Window* window;
    SDL_Renderer *renderer;


}App;

typedef struct
{
    TTF_Font* font;
}Resources;

typedef struct
{
    bool metronome_running;
    bool is_dragging;
    int bpm;
    const int bpm_max;
    const int bpm_min;
    char bpm_text[3];
}Metronome;

typedef struct
{
    SDL_FRect run_metronome_rect;
    SDL_FRect slider_bar;
    SDL_FRect slider_knob;

    SDL_FRect bpm_display;
}UI;

typedef struct
{
    App app;
    Resources resources;
    Metronome metronome;
    UI ui;
}Context;

void init(Context* context);


#endif