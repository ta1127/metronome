#include <SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<stdio.h>
#include"utility.h"

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
    int bpm_max;
    int bpm_min;
}Metronome;

typedef struct
{
    SDL_FRect run_metronome_rect;
    SDL_FRect slider_bar;
    SDL_FRect slider_knob;

    char bpm_text[3];
    SDL_FRect bpm_display;
}UI;

typedef struct
{
    App app;
    Resources resources;
    Metronome metronome;
    UI ui;
}Variables;


void init(Variables* v)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    v -> app.window = SDL_CreateWindow("TA_Metronome", 640, 480, 0);
    v -> app.renderer = SDL_CreateRenderer(v -> app.window,NULL);
    if(!v -> app.window || !v -> app.renderer)
    {
        printf("SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    v -> resources.font = TTF_OpenFont("4x4kanafont.ttf",24);

    v -> app.running = true;
    v -> metronome.metronome_running = false;
    v -> metronome.is_dragging = false;
    

    v -> ui.run_metronome_rect = create_rect(100.0f,100.0f,100.0f,50.0f);
    v -> ui.slider_bar = create_rect(200.0f,200.0f,200.0f,10.0f);
    v -> ui.slider_knob = create_rect(v -> ui.slider_bar.x + v -> metronome.bpm * v -> ui.slider_bar.w / (v -> metronome.bpm_max-v -> metronome.bpm_min),190.0f,20.0f,20.0f);

    v -> ui.bpm_display = create_rect(100.0f, 50.0f, 100.0f, 50.0f);



    v -> metronome.bpm=120;
    v -> metronome.bpm_max = 300;
    v -> metronome.bpm_min = 30;
    metronome_init(v -> metronome.bpm);

    
    
    v -> ui.bpm_text[3] = "120";

}