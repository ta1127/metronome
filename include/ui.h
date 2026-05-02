#ifndef UI_H
#define UI_H

#include<SDL3\SDL.h>

//slider
typedef struct
{
    SDL_FRect slider_bar;
    SDL_FRect slider_knob;
    float max;
    float min;
    bool is_dragging;

}Slider;

Slider init_slider(SDL_FRect slider_bar,SDL_FRect slider_knob,float max,float min);
float slider_get_value(Slider* slider,SDL_Event event);

#endif