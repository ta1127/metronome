#include <SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<stdio.h>
#include"init.h"
#include"metronome.h"
#include "utility.h"
#include"poll_event.h"
#include"ui.h"

void init(Variables* v)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    TTF_Init();

    v -> app.window = SDL_CreateWindow("TA_Metronome", 640, 480, 0);
    v -> app.renderer = SDL_CreateRenderer(v -> app.window,NULL);
    if(!v -> app.window || !v -> app.renderer)
    {
        printf("SDL Error: %s\n", SDL_GetError());
        return;
    }

    v -> resources.font = TTF_OpenFont("4x4kanafont.ttf",24);

    v -> app.running = true;
    v -> metronome.metronome_running = false;

    
    v -> metronome.bpm=120;
    int bpm_max = 400;
    int bpm_min = 30;

    v -> ui.run_metronome_rect = create_rect(100.0f,100.0f,100.0f,50.0f);

    SDL_FRect slider_bar = create_rect(200.0f,200.0f,200.0f,10.0f);
    SDL_FRect slider_knob = create_rect(slider_bar.x + (v -> metronome.bpm - bpm_min) * slider_bar.w / (float)(bpm_max-bpm_min),190.0f,20.0f,20.0f);
    v -> ui.slider = init_slider(slider_bar,slider_knob,bpm_max,bpm_min);

    v -> ui.bpm_display = create_rect(100.0f, 50.0f, 100.0f, 50.0f);

    init_metronome(v -> metronome.bpm);

    sprintf(v -> ui.bpm_text,"%d",v -> metronome.bpm);
    

}