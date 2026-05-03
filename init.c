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

    v->metronome.timesignature.beats_per_measure = 4;
    v->metronome.timesignature.note_value = 4;
    v->metronome.timesignature.current_beat = 1;

    
    v -> metronome.bpm=120;
    int bpm_max = 400;
    int bpm_min = 30;

    v -> ui.run_metronome_button = init_button(100.0f,100.0f,100.0f,50.0f,(SDL_Color){0, 255, 0, 255});

    
    v -> ui.slider = init_slider(200.0f,200.0f,200.0f,10.0f,20.0f,bpm_max,bpm_min,(SDL_Color){200, 200, 200,255},(SDL_Color){255, 0, 0,255});
    slider_set_value(&v -> ui.slider,v -> metronome.bpm);

    v -> ui.bpm_display = create_rect(100.0f, 50.0f, 100.0f, 50.0f);

    init_metronome(v);

    sprintf(v -> ui.bpm_text,"%d",v -> metronome.bpm);
    

}