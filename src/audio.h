#ifndef AUDIO_H
#define AUDIO_H

#include "raylib.h"

// Attach a processor to the audio stream to perform FFT
void attach_audio_processor(Music music);

// Detach the audio processor
void detach_audio_processor(Music music);

// Get the latest FFT data
void get_fft_data(double *fft_data, int data_size);

#endif //AUDIO_H