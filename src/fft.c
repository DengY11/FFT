#include "fft.h"
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include "define.h"
#define PI 3.14159265358979323846

typedef struct {
    double *in;
    Complex *out;
    int size;
    int start_k;
    int end_k;
} ThreadArgs;

void* dft_worker(void *args) {
    ThreadArgs *t_args = (ThreadArgs*)args;
    double *in = t_args->in;
    Complex *out = t_args->out;
    int size = t_args->size;

    for (int k = t_args->start_k; k < t_args->end_k; k++) {
        out[k].real = 0;
        out[k].imag = 0;
        for (int n = 0; n < size; n++) {
            double angle = -2 * PI * k * n / size;
            out[k].real += in[n] * cos(angle);
            out[k].imag += in[n] * sin(angle);
        }
    }
    return NULL;
}

void perform_fft(double *in, Complex *out, int size) {
    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];
    int k_per_thread = (size / 2 + 1) / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].in = in;
        thread_args[i].out = out;
        thread_args[i].size = size;
        thread_args[i].start_k = i * k_per_thread;
        thread_args[i].end_k = (i == NUM_THREADS - 1) ? (size / 2 + 1) : (i + 1) * k_per_thread;
        pthread_create(&threads[i], NULL, dft_worker, &thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}