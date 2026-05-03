#ifndef METRONOME_H
#define METRONOME_H

#include"init.h"

void init_metronome(Variables* v);
void metronome_set_bpm(int bpm);
void metronome_run(Metronome* metronome);

#endif