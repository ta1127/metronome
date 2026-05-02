#include <SDL3/SDL.h>
#include<stdio.h>
#include"utility.h"
#include"ui.h"
#include"metronome.h"
//slider
Slider init_slider(SDL_FRect slider_bar,SDL_FRect slider_knob,float max,float min)
{
    Slider slider;
    slider.slider_bar = slider_bar;
    slider.slider_knob = slider_knob;
    slider.max = max;
    slider.min = min;
    slider.is_dragging = false;

    return slider;
}

float slider_get_value(Slider* slider,SDL_Event event)
{
    float slider_value = slider->min + (slider->max-slider->min)*(slider->slider_knob.x - slider->slider_bar.x)/slider->slider_bar.w;

        
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    { 

        if(has_clicked(slider->slider_knob,event))
        {
            slider->is_dragging = true;
        }

        if(has_clicked(slider->slider_bar,event))
        {
            slider->slider_knob.x = event.button.x;
            slider_value = slider->min + (slider->max - slider->min) * (slider->slider_knob.x-slider->slider_bar.x)/slider->slider_bar.w;
        }          
    }

    if(event.type == SDL_EVENT_MOUSE_MOTION && slider->is_dragging)
    {
        float mouse_x = event.motion.x;

        if(mouse_x <= slider->slider_bar.x + slider->slider_bar.w && mouse_x >= slider->slider_bar.x)
        {
            slider->slider_knob.x = mouse_x;
            slider_value = slider->min + (slider->max - slider->min) * (slider->slider_knob.x-slider->slider_bar.x)/slider->slider_bar.w; 
        }
        else if(mouse_x < slider->slider_bar.x)
        {
            slider->slider_knob.x = slider->slider_bar.x;
            slider_value = slider->min;
        }
        else if(mouse_x > slider->slider_bar.x + slider->slider_bar.w)
        {
            slider->slider_knob.x = slider->slider_bar.x + slider->slider_bar.w; 
            slider_value = slider->max;
        }
    }

    if(event.type == SDL_EVENT_MOUSE_BUTTON_UP && slider->is_dragging)
    {
        slider->is_dragging = false;
    }

    
    return slider_value;
}