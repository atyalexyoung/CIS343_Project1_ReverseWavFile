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
int get_header(struct wav_file* audio)
{
    int riff_status, file_type_status, format_chunk_status, data_header_status;

    // get riff and check if riff
    
    riff_status = check_riff(&audio->wav_header_pointer[0]);
    if(riff_status != 0)
    {
        return 1;
    }

    // get file type and check if 'WAVE'
    
    file_type_status = check_file_type(&audio->wav_header_pointer[8]);
    if(file_type_status != 0)
    {
        return 1;
    }

    // get format chunk and check if 'fmt'
    
    format_chunk_status = check_format_chunk_status(&audio->wav_header_pointer[12]);
    if(format_chunk_status != 0)
    {
        return 1;
    }

    // get data header and check if 'data' 36-39
    
    data_header_status = check_header_status(&audio->wav_header_pointer[36]);
    if(data_header_status != 0)
    {
        return 1;
    }    

    // NEED TO BE PRINTED OUT
    audio->wav_header_pointer->num_channels = &audio->wav_header_pointer[22]; // 22-23
    audio->wav_header_pointer->sample_rate = &audio->wav_header_pointer[24];// 24-27
    //********************************************

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



