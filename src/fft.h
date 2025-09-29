#ifndef FFT_H
#define FFT_H



typedef struct {
    double real;
    double imag;
} Complex;

// Perform a Discrete Fourier Transform (DFT)
void perform_fft(double *in, Complex *out, int size);

#endif //FFT_H