#include <SDL3/SDL.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<stdio.h>
#include<time.h>
#include"init.h"
#include"metronome.h"
#include "utility.h"
#include"poll_event.h"
#include"renderer.h"
#include"ending.h"


int main(int argc, char* argv[]) 
{
    Variables v;
    

    init(&v);

    while(v.app.running)
    {

        poll_event(&v);
        //software functions
        if(v.metronome.metronome_running)
        {
            metronome_run(&v.metronome);
        }    

        render(&v);
    
        SDL_Delay(1);//resting cpu

    }

    ending_program(&v);


    return 0;
    
}

