#include"metronome.h"
#include<stdio.h>
#include<SDL3/SDL.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>


#define SAMPLE_RATE 44100
#define DURATION 0.05   // 50ms

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

float* generate_beep(float freq)
{
    
    float* beep = malloc(sizeof(float) * 2205);

    for(int i = 0; i < SAMPLE_RATE * DURATION; i++)
    {
        beep[i] = 0.3f * sinf(2.0f * 3.14159f * freq * i / SAMPLE_RATE);
    }
    return beep;
}

void init_metronome(Variables* v)
{
    
    SDL_zero(mv.audio_spec);
    mv.audio_spec.freq = 44100;
    mv.audio_spec.format =SDL_AUDIO_F32;
    mv.audio_spec.channels = 1;

    mv.dev = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,&mv.audio_spec);
    mv.stream = SDL_CreateAudioStream(&mv.audio_spec,&mv.audio_spec);
    SDL_BindAudioStream(mv.dev,mv.stream);
    SDL_ResumeAudioDevice(mv.dev);

    v->metronome.sound.sound_1 = generate_beep(880.0f);
    v->metronome.sound.sound_2 = generate_beep(440.0f);
    v -> metronome.sound.sound_length = (int)(SAMPLE_RATE * DURATION);

    clock_gettime(CLOCK_MONOTONIC,&ts);
    mv.now = ts.tv_sec + ts.tv_nsec/1e9;
    mv.next = mv.now;
    mv.interval = 60.0f/(float)v -> metronome.bpm;
    printf("%d",v -> metronome.bpm);
}

void metronome_set_bpm(int bpm)
{

    mv.interval = 60.0f/(float)bpm;
    printf("%d",bpm);
}

void metronome_run(Metronome* metronome){

    clock_gettime(CLOCK_MONOTONIC,&ts);
    mv.now = ts.tv_sec + ts.tv_nsec/1e9;
    if(mv.next <= mv.now)
    {
        if(metronome->timesignature.current_beat == 1)
        {
            SDL_PutAudioStreamData(mv.stream,metronome->sound.sound_1,sizeof(float) * metronome->sound.sound_length);
        }
        else if(metronome->timesignature.current_beat != 1)
        {
            SDL_PutAudioStreamData(mv.stream,metronome->sound.sound_2,sizeof(float) * metronome->sound.sound_length);
        }
        printf("tick!");
        
        mv.next = mv.now + mv.interval;

        metronome->timesignature.current_beat ++;

        if(metronome->timesignature.current_beat == metronome->timesignature.beats_per_measure + 1)
        {
            metronome->timesignature.current_beat = 1;
        }
    }

}