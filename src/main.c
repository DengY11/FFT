#include <stdio.h>
#include "raylib.h"
#include "audio.h"
#include "visual.h"
#include "define.h"


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <mp3_file>\n", argv[0]);
        return 1;
    }

    const char *mp3_file = argv[1];

    InitAudioDevice();
    init_visualizer(SCREEN_WIDTH, SCREEN_HEIGHT, "Music Visualizer");

    Music music = LoadMusicStream(mp3_file);
    if (music.stream.buffer == NULL) {
        printf("Failed to load music file: %s\n", mp3_file);
        return 1;
    }

    attach_audio_processor(music);
    PlayMusicStream(music);

    double visual_data[FFT_SIZE];

    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        get_fft_data(visual_data, FFT_SIZE);
        update_visualizer(visual_data, FFT_SIZE);
    }

    detach_audio_processor(music);
    UnloadMusicStream(music);
    close_visualizer();
    CloseAudioDevice();

    return 0;
}