#include"metronome.h"
#include<stdio.h>
#include<SDL3/SDL.h>
#include<time.h>
#include<math.h>


typedef struct 
{
    
    double now, next;
    double interval;
    SDL_AudioSpec audio_spec;
    SDL_AudioDeviceID dev;
    SDL_AudioStream* stream;

}metronome_valuable;
static metronome_valuable mv;

static struct timespec ts;

#define SAMPLE_RATE 44100
#define DURATION 0.05   // 50ms

float beep[44100/20];

void generate_beep()
{
    float freq = 1320.0f;

    for(int i = 0; i < SAMPLE_RATE * DURATION; i++)
    {
        beep[i] = 0.3f * sinf(2.0f * 3.14159f * freq * i / SAMPLE_RATE);
    }
}

void init_metronome(int bpm)
{
    
    SDL_zero(mv.audio_spec);
    mv.audio_spec.freq = 44100;
    mv.audio_spec.format =SDL_AUDIO_F32;
    mv.audio_spec.channels = 1;

    mv.dev = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,&mv.audio_spec);
    mv.stream = SDL_CreateAudioStream(&mv.audio_spec,&mv.audio_spec);
    SDL_BindAudioStream(mv.dev,mv.stream);
    SDL_ResumeAudioDevice(mv.dev);



    generate_beep();


    
    clock_gettime(CLOCK_MONOTONIC,&ts);
    mv.now = ts.tv_sec + ts.tv_nsec/1e9;
    mv.next = mv.now;
    mv.interval = 60.0f/(float)bpm;
    printf("%d",bpm);
}

void metronome_set_bpm(int bpm)
{
    clock_gettime(CLOCK_MONOTONIC,&ts);
    mv.now = ts.tv_sec + ts.tv_nsec/1e9;
    mv.next = mv.now;
    mv.interval = 60.0f/(float)bpm;
    printf("%d",bpm);
}

void metronome_run(){

    clock_gettime(CLOCK_MONOTONIC,&ts);
    mv.now = ts.tv_sec + ts.tv_nsec/1e9;
    if(mv.next <= mv.now)
    {
        printf("tick!");
        SDL_PutAudioStreamData(mv.stream, beep, sizeof(beep));
        mv.next = mv.now + mv.interval;
    }

}