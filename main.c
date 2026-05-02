#include <SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<stdio.h>
#include<time.h>
#include"init.h"
#include"metronome.h"
#include "utility.h"


int main(int argc, char* argv[]) 
{
    Variables v;
    SDL_Color text_color = {255,255,255,255};

    init(&v);

    



    
    



    while(v.app.running)
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
                    sprintf(v.metronome.bpm_text,"%d",v.metronome.bpm);
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
                sprintf(v.metronome.bpm_text,"%d",v.metronome.bpm);
                printf("%d ",v.metronome.bpm);
                metronome_init(v.metronome.bpm);
            }

            if (event.type == SDL_EVENT_KEY_DOWN) 
            {
                printf("KeyPressec");

                return 0;
            }   
        }

        //software functions
        if(v.metronome.metronome_running)
        {
            
            metronome_run();
        }    
        
        // 画面クリア
        SDL_SetRenderDrawColor(v.app.renderer, 0, 0, 0, 255);
        SDL_RenderClear(v.app.renderer);

        // ボタン描画
        SDL_SetRenderDrawColor(v.app.renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(v.app.renderer, &v.ui.run_metronome_rect);

        //スライダー描画
        // バー
        SDL_SetRenderDrawColor(v.app.renderer, 200, 200, 200, 255);
        SDL_RenderFillRect(v.app.renderer, &v.ui.slider_bar);

        // つまみ
        SDL_SetRenderDrawColor(v.app.renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(v.app.renderer, &v.ui.slider_knob);

        SDL_Surface* surface = TTF_RenderText_Solid(v.resources.font, v.metronome.bpm_text, strlen(v.metronome.bpm_text), text_color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(v.app.renderer, surface);

        SDL_FRect bpm_display = {100, 50, surface->w, surface->h};
        SDL_RenderTexture(v.app.renderer, texture, NULL, &bpm_display);

        
        // 表示
        SDL_RenderPresent(v.app.renderer);

        SDL_DestroySurface(surface);
        SDL_DestroyTexture(texture);

        SDL_Delay(1);//resting cpu

    }
    
}

