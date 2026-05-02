#include <SDL3/SDL.h>
#include<stdio.h>
#include"init.h"
#include"metronome.h"
#include "utility.h"

void poll_event(Variables v)
{
    
    SDL_Event event;

    //イベント処理
    while (SDL_PollEvent(&event)) //events
    {

        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        { 

            if(has_clicked(v.ui.run_metronome_rect,event))
            {
                v.metronome.metronome_running = !v.metronome.metronome_running;
            }

            if(has_clicked(v.ui.slider_knob,event))
            {
                v.metronome.is_dragging = true;
            }

            if(has_clicked(v.ui.slider_bar,event))
            {
                v.ui.slider_knob.x = event.button.x;
                v.metronome.bpm = SDL_round( v.metronome.bpm_min + (v.metronome.bpm_max - v.metronome.bpm_min) * (v.ui.slider_knob.x-v.ui.slider_bar.x)/v.ui.slider_bar.w);
                metronome_init(v.metronome.bpm);
                sprintf(v.ui.bpm_text,"%d",v.metronome.bpm);
                printf("%d ",v.metronome.bpm);
            }
            if(has_clicked(v.ui.bpm_display,event))
            {
                SDL_StartTextInput(v.app.window);
            }
                   
        }

        if(event.type == SDL_EVENT_MOUSE_MOTION && v.metronome.is_dragging)
        {
            float mouse_x = event.motion.x;

            if(mouse_x <= v.ui.slider_bar.x + v.ui.slider_bar.w && mouse_x >= v.ui.slider_bar.x)
            {
                v.ui.slider_knob.x = mouse_x;
                v.metronome.bpm = SDL_round( v.metronome.bpm_min + (v.metronome.bpm_max - v.metronome.bpm_min) * (v.ui.slider_knob.x-v.ui.slider_bar.x)/v.ui.slider_bar.w); 
            }
            else if(mouse_x < v.ui.slider_bar.x)
            {
                v.ui.slider_knob.x = v.ui.slider_bar.x;
                v.metronome.bpm = v.metronome.bpm_min;
            }
            else if(mouse_x > v.ui.slider_bar.x + v.ui.slider_bar.w)
            {
                v.ui.slider_knob.x = v.ui.slider_bar.x + v.ui.slider_bar.w; 
                v.metronome.bpm = v.metronome.bpm_max;
            }
        }

        if(event.type == SDL_EVENT_MOUSE_BUTTON_UP && v.metronome.is_dragging)
        {
            v.metronome.is_dragging = false;
            sprintf(v.ui.bpm_text,"%d",v.metronome.bpm);
            printf("%d ",v.metronome.bpm);
            metronome_init(v.metronome.bpm);
        }

        if (event.type == SDL_EVENT_KEY_DOWN) 
        {
            printf("KeyPressec");
            v.app.running = false;
        }   
    }
}