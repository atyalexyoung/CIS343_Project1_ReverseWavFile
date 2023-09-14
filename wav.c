#include <stdio.h>
#include <stdlib.h>
#include "wav.h"
#include "file_lib.h"

/**
 * The following functions check that the file has all the correct attributes and is the right type
*/
int check_riff(char* start)
{
    printf("Checking RIFF and got: ");
    for(int i = 0; i < 4; i++)
    {
        printf("%c",start[i]);
    }

    if(*start == 'R' && *(start + 1) == 'I' && *(start + 2) == 'F' && *(start + 3) == 'F')
    {
        printf("\n");
        return 0;
    }
    printf("\n");
    return 1;
}


int check_file_type(char* start)
{
    printf("Checking WAVE and got: ");
    for(int i = 8; i < 12; i++)
    {
        printf("%c",start[i]);
    }

    if(start[8] == 'W' && start[9] == 'A' && start[10] == 'V' && start[11] == 'E')
    {
        printf("\n");
        return 0;
    }
    printf("\n");
    return 1;
    
}


int check_format_chunk_status(char* start)
{
    printf("Checking fmt and got: ");
    for(int i = 12; i < 16; i++)
    {
        printf("%c",start[i]);
    }
    
    if(start[12] == 'f' && start[13] == 'm' && start[14] == 't')
    {
        printf("\n");
        return 0;
    }
    printf("\n");
    return 3;
}


int check_header_status(char* start)
{
    printf("Checking data and got: ");
    for(int i = 36; i < 40; i++)
    {
        printf("%c",start[i]);
    }
    
    if(start[36] == 'd' && start[37] == 'a' && start[38] == 't' && start[39] == 'a')
    {
        printf("\n");
        return 0;
    }
    printf("\n");
    return 4;
    
}

int check_format_type(char* start)
{
    short* i = (short*)&start[20];
    short x = *i;

    if(x == 1)
    {
        return 0;
    }
    return 5;
}

int check_num_channels(char* start)
{
    short* i = (short*)&start[22];

    short x = *i;

    if(x == 2)
    {
        return 0;
    }
    return 6;
}


/***
 * This function takes a file path as a parameter
 * It sets a variable "size" to the size of the wav file
 * Returns a "wav_file" struct 
*/
struct wav_file load_file(char* file_path)
{
    size_t size;
    struct wav_file audio;
    char* file_contents = read_file(file_path, &size);
    if(file_contents == NULL)
    {
        printf("Error reading in the file \n");
    }


    // SHOULD WE DO THIS INSTEAD SINCE WE KNOW IT WILL ALWAYS BE 44????
    //char header_content[44] = file_contents;
    audio.original_data = file_contents;
    audio.file_size = size;
    // SHOULD WE MAKE THIS AN ARRAY ALSO INSTEAD OF A POINTER
    audio.data = &file_contents[44];


    // SHOULD WE FREE THE FILE CONTENTS OR WOULD THAT GET RID OF OUR POINTERS
    free(file_contents);
    return audio;
}

/**
 * This function will write a wav file to disk from memory,
 * returns errorno
*/
int save_file(char* reversed, size_t byte_array_size, char* file_path)
{
    int errorno = write_file(file_path, reversed, byte_array_size);

    if(errorno != 0)
    {
        printf("Mission failed. We'll get em' next time\" - Captain Price \n");
        return errorno;
    }

    printf("Mission successful \n");
    return errorno;
}


/**
 * This function takes a "wav_file" struct as a parameter. It then populates the "wav_header" struct within it.
 * Returns an integer that is the error number
*/
int get_header(struct wav_file* audio)
{

    // Getting variables for from the wav header, and checking their values to proceed.

    //THIS IS THE RIGHT WAY TO DO IT PER WOODRING
    int riff_status = check_riff(audio->original_data);
    if(riff_status != 0)
    {
        return 1;
    }

    int file_type_status = check_file_type(audio->original_data);
    if(file_type_status != 0)
    {
        return 2;
    }

    int format_chunk_status = check_format_chunk_status(audio->original_data);
    if(format_chunk_status != 0)
    {
        return 3;
    }

    int data_header_status = check_header_status(audio->original_data);
    if(data_header_status != 0)
    {
        return 4;
    }    

    int format_type_status = check_format_type(audio->original_data);
    if(format_type_status != 0)
    {
        return 5;
    }

    int num_channels_status = check_num_channels(audio->original_data);
    if(num_channels_status != 0)
    {
        return 6;
    }


    // Setting variables in the wav_header struct and printing their values out
    //audio->wav_header_pointer->num_channels = &audio->wav_header_pointer[22]; // 22-23
    //printf("Number of channels: %d \n",audio->wav_header_pointer->num_channels);

    // get the bits per sample to be the step size while reversing
    //audio->wav_header_pointer->bits_per_sample = &audio->wav_header_pointer[34]; // 34 - 35
    //printf("Bits per sample: %d \n", audio->wav_header_pointer->bits_per_sample);


    return 0;
}


// WE ALSO NEED TO CHECK THE FILE HAS 2 CHANNELS
// WE ALSO NEED TO CHEC KTHAT THE FORMAT TYPE IS THE VALUE 1
// WE ALSO NEED TO CHECK THAT THE INTEGER IN BYTES 4-7 IS THE (FILE_SIZE - 8)


