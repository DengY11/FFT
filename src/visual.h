#ifndef VISUAL_H
#define VISUAL_H

#include "raylib.h"
#include "define.h"


// Initialize the visualizer window
void init_visualizer(int width, int height, const char *title);

// Update and draw the visualizer
void update_visualizer(double *fft_data, int data_size);

// Close the visualizer window
void close_visualizer(void);

#endif //VISUAL_H