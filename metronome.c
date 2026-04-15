#include"metronome.h"
#include<stdio.h>
#include<SDL3/SDL.h>
#include<time.h>

double now, next,interval;
struct timespec ts;

void metronome_init(double bpm){
    
    
    clock_gettime(CLOCK_MONOTONIC,&ts);
    now = ts.tv_sec + ts.tv_nsec/1e9;
    next = now;
    interval = 60/bpm;
}

void metronome_run(){

    clock_gettime(CLOCK_MONOTONIC,&ts);
    now = ts.tv_sec + ts.tv_nsec/1e9;
    if(next <= now)
    {
            printf("tick!");
            next = now + interval;
    }

}