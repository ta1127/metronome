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

    SDL_Color slider_bar_color;
    SDL_Color slider_knob_color;

}Slider;

Slider init_slider(float slider_bar_x,float slider_bar_y,float slider_bar_w,float slider_knob_l,float slider_bar_h,float max,float min,SDL_Color slider_bar_color,SDL_Color slider_knob_color);
float slider_get_value(Slider* slider,SDL_Event event);
void slider_set_value(Slider* slider,float slider_value);

//button
typedef struct
{
    SDL_FRect button;

    SDL_Color button_color;
}Button;

Button init_button(float button_x,float button_y,float button_w,float button_h,SDL_Color button_color);


#endif