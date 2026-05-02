#include <SDL3/SDL.h>
#include<stdio.h>
#include"init.h"
#include"metronome.h"
#include "utility.h"
#include"ui.h"

void slider_update_bpm(Variables* v,SDL_Event event)
{
    v -> metronome.bpm = SDL_roundf(slider_get_value(&v->ui.slider,event));
    sprintf(v -> ui.bpm_text,"%d",v -> metronome.bpm);
    
}

void poll_event(Variables* v)
{
    
    SDL_Event event;

    //イベント処理
    while (SDL_PollEvent(&event)) //events
    {

        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        { 
            if(has_clicked(v->ui.run_metronome_rect,event))
            {
                v->metronome.metronome_running = !v->metronome.metronome_running;
            }
            if(has_clicked(v->ui.bpm_display,event))
            {
                SDL_StartTextInput(v->app.window);
            }

            if(has_clicked(v->ui.slider.slider_bar,event))
            {
                metronome_set_bpm(v -> metronome.bpm);
            }
                   
        }
        if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
        {
            if(has_clicked(v->ui.slider.slider_bar,event))
            {
                metronome_set_bpm(v -> metronome.bpm);
            }
        }

        slider_update_bpm(v,event);
        
        if (event.type == SDL_EVENT_KEY_DOWN) 
        {
            printf("KeyPressec");
            v->app.running = false;
        }   
    }
}

