#include <stdio.h>
#include "wav.h"
#include "file_lib.h"

/**
 * returns a pointer to a wav_file struct
*/
struct wav_file load_file(char* file_path)
{
    size_t size;
    struct wav_file audio;
    char* file_contents = read_file(file_path, &size);

    audio.wav_header_pointer = file_contents;
    audio.file_size = size;
    audio.data = file_contents[40];

    free(file_contents);
    return audio;
}

/**
 * returns errorno, writes to disk
*/
int save_file(struct wav_file audio, char* file_path)
{
    int errorno = write_file(file_path, audio.wav_header_pointer, audio.file_size);

    if(errorno != 0)
    {
        printf("Mission failed. We'll get em' next time\" - Captain Price");
        return errorno;
    }

    printf("Mission successful");
    return errorno;
}

/**
 * return the errorno, and will set the wav_header that is passed in
*/

//pass in pointer to the wav_file struct... no need to pass in wav_header nbecause we havea  wav_header in the wav_file
int get_header(struct wav_file audio, struct wav_header header)
{
    int riff_status, file_type_status, format_chunk_status, data_header_status;

    // get riff and check if riff
    header.riffy_boi = audio.wav_header_pointer;
    riff_status = check_riff(header.riffy_boi);
    if(riff_status != 0)
    {
        return 1;
    }

    // get file type and check if 'WAVE'
    header.file_type = &audio.wav_header_pointer[8];
    file_type_status = check_file_type(header.file_type);
    if(file_type_status != 0)
    {
        return 1;
    }

    // get format chunk and check if 'fmt'
    header.format_chunk = &audio.wav_header_pointer[12];
    format_chunk_status = check_format_chunk_status(header.format_chunk);
    if(format_chunk_status != 0)
    {
        return 1;
    }

    // get data header and check if 'data' 36-39
    header.data_header = &audio.wav_header_pointer[36];
    data_header_status = check_header_status(header.data_header);
    if(data_header_status != 0)
    {
        return 1;
    }    

    // NEED TO BE PRINTED OUT
    header.num_channels = &audio.wav_header_pointer[22]; // 22-23
    header.sample_rate = &audio.wav_header_pointer[24]; // 24-27
    //********************************************


    // useless??? not as useless as me
    header.num_bytes = &audio.wav_header_pointer[4]; // number of bytes after subracting 8 4-7
    header.length_of_format_data = &audio.wav_header_pointer[16]; //16-19
    header.format_type = &audio.wav_header_pointer[20]; // 20-21
    header.bits_per_sample = &audio.wav_header_pointer[34]; // 34-35
    header.data_section_size = &audio.wav_header_pointer[34]; // 40-43

    return 0;
}

// guess what these functions doo
int check_riff(char* start)
{
    if(start == 'R' && (start + 1) == 'I' && *(start + 2) == 'F' && (start + 3) == 'F')
    {
        return 0;
    }
    return 1;
}

int check_file_type(char* start)
{
    if(start == 'W' && (start + 1) == 'A' && *(start + 2) == 'V' && (start + 3) == 'E')
    {
        return 0;
    }
    return 1;
}


int check_format_chunk_status(char* start)
{
    if(start == 'f' && (start + 1) == 'm' && *(start + 2) == 't')
    {
        return 0;
    }
    return 1;
}


int check_header_status(char* start)
{
    if(start == 'd' && (start + 1) == 'a' && *(start + 2) == 't' && (start + 3) == 'a')
    {
        return 0;
    }
    return 1;
}



