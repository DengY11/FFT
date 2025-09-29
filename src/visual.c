#include "visual.h"
#include "raylib.h"
#include <stdlib.h>
#include <math.h>

// Apply a logarithmic curve to the height, making lower values more visible.
static double normalize_height(double height) {
    // log1p(x) = log(1+x)
    // We use it to map the linear input height [0, 1] to a logarithmic scale.
    double log_height = log1p(height * 9); // Multiply by 9 to stretch the input range to [0, 9]
    double log_max = log1p(9.0); // The max value of our log scale
    double normalized = log_height / log_max; // Normalize back to [0, 1]
    return normalized * GAIN;
}

void init_visualizer(int width, int height, const char *title) {
    InitWindow(width, height, title);
    SetTargetFPS(60);
}

void update_visualizer(double *fft_data, int data_size) {
    BeginDrawing();
    ClearBackground(BLACK);

    if (fft_data != NULL) {
        int display_data_size = (int)(data_size * MAX_FREQ_RATIO);
        if (display_data_size <= 1) return; 

        for (int i = 0; i < display_data_size; i++) {
            int x = (int)((double)i / display_data_size * GetScreenWidth());
            int next_x = (int)((double)(i + 1) / display_data_size * GetScreenWidth());
            int bar_width = next_x - x;
            if (bar_width < 1) bar_width = 1;

            double normalized_h = normalize_height(fft_data[i]);
            int bar_height = (int)(normalized_h * (double)GetScreenHeight());
            
            int y = GetScreenHeight() - bar_height;
            DrawRectangle(x, y, bar_width, bar_height, LIME);
        }
    }

    EndDrawing();
}

void close_visualizer(void) {
    CloseWindow();
}