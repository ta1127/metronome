#include <SDL3/SDL.h>
#include<stdio.h>
#include"utility.h"
#include"ui.h"
#include"metronome.h"
//slider
Slider init_slider(float slider_bar_x,float slider_bar_y,float slider_bar_w,float slider_bar_h,float slider_knob_l,float max,float min,SDL_Color slider_bar_color,SDL_Color slider_knob_color)
{
    Slider slider;
    slider.slider_bar = create_rect(slider_bar_x,slider_bar_y,slider_bar_w,slider_bar_h);
    slider.slider_knob = create_rect(slider_bar_x,slider_bar_y,slider_knob_l,slider_knob_l);
    slider.max = max;
    slider.min = min;
    slider.is_dragging = false;

    slider.slider_bar_color = slider_bar_color;
    slider.slider_knob_color = slider_knob_color;

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

void slider_set_value(Slider* slider,float slider_value)
{
    slider->slider_knob.x = slider -> slider_bar.x + (slider_value - slider -> min) * slider -> slider_bar.w / (float)(slider -> max - slider -> min);
}

//button

Button init_button(float button_x,float button_y,float button_w,float button_h,SDL_Color button_color)
{
    Button button;
    button.button = create_rect(button_x,button_y,button_w,button_h);

    return button;

}

