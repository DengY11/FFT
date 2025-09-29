#include "audio.h"
#include "fft.h"
#include <string.h>
#include <math.h>
#include <pthread.h>

static double fft_input[FFT_SIZE];
static Complex fft_output[FFT_SIZE / 2 + 1];
static double visual_output[FFT_SIZE / 2];
static int buffer_pos = 0;

static pthread_mutex_t fft_mutex = PTHREAD_MUTEX_INITIALIZER;

void process_audio(void *buffer, unsigned int frames) {
    float *samples = (float*)buffer;

    for (unsigned int i = 0; i < frames; i++) {
        fft_input[buffer_pos] = (double)(samples[i*2] + samples[i*2 + 1]) / 2.0;
        buffer_pos++;
        if (buffer_pos >= FFT_SIZE) {
            perform_fft(fft_input, fft_output, FFT_SIZE);
            pthread_mutex_lock(&fft_mutex);
            for (int j = 0; j < FFT_SIZE / 2; j++) {
                double magnitude = sqrt(fft_output[j].real * fft_output[j].real + fft_output[j].imag * fft_output[j].imag);
                visual_output[j] = magnitude / (FFT_SIZE * 5.0);
            }
            pthread_mutex_unlock(&fft_mutex);
            buffer_pos = 0;
        }
    }
}

void attach_audio_processor(Music music) {
    AttachAudioStreamProcessor(music.stream, process_audio);
}

void detach_audio_processor(Music music) {
    DetachAudioStreamProcessor(music.stream, process_audio);
}

void get_fft_data(double *fft_data, int data_size) {
    pthread_mutex_lock(&fft_mutex);
    memcpy(fft_data, visual_output, data_size * sizeof(double));
    pthread_mutex_unlock(&fft_mutex);
}