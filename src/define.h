#ifndef DEFINE_H
#define DEFINE_H

// Screen dimensions
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

// FFT and Audio settings
#define FFT_SIZE (2 << 10) // Size of the FFT buffer (must be a power of 2)

// Visualizer settings
#define MAX_FREQ_RATIO 0.038// Ratio of the frequency spectrum to display (0.0 to 1.0)
#define GAIN  15.0           // Y-axis scaling factor

#define NUM_THREADS 16

#endif //DEFINE_H