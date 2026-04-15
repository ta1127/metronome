#include <SDL3/SDL.h>
#include<stdio.h>
#include<time.h>
#include"metronome.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Hello SDL3", 640, 480, 0);
    SDL_Event event;
    
    double bpm=120;
    
    bool running = true;
    bool metronome_running = false;

    
    



    while(running)
    {
        while (SDL_PollEvent(&event)) 
        {

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            { 
                metronome_running = !metronome_running;
                metronome_init(bpm);   
            }

            if (event.type == SDL_EVENT_KEY_DOWN) {
                printf("KeyPressec");

                return 0;
            }   
        }

        if(metronome_running)
        {
            metronome_run();
        }      

        
        SDL_Delay(1);

    }


   
    
                
        

    

    
}