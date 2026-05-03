#ifndef INIT_H
#define INIT_H

#include <SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>
#include"ui.h"

typedef struct 
{
    bool running;

    SDL_Window* window;
    SDL_Renderer *renderer;


}App;


typedef struct
{
    float*  sound_1;
    float* sound_2;
    int sound_length;
}Sound;

typedef struct
{
    TTF_Font* font;
    
}Resources;

typedef struct 
{
    int beats_per_measure;
    int note_value;

    int current_beat;
}Timesignature;



typedef struct
{
    bool metronome_running;
    int bpm;
    Sound sound;
    Timesignature timesignature;
    
}Metronome;

typedef struct
{
    Button run_metronome_button;

    Slider slider;


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

void init(Variables* variables);


#endif