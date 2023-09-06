#include <stdio.h>
#include "wav.h"






int load_file(char* data){
    size_t size;
    char* file_contents = read_file("Abdication.wav", &size);
    struct wav_file audio;
    audio.wav_header_pointer = file_contents;
    audio.file_size = size;
    audio.data = file_contents[44];

    return;
}
