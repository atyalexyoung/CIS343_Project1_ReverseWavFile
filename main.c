#include <stdio.h>
#include <stdlib.h>
#include "wav.h"
#include "file_lib.h"
#include <string.h>


int print_error_message(int error)
{
    /**
     * Checking which part of the wav file caused the issue based on the errorno
    */
    switch (error)
    {
    case 1:
        printf("The first 4 bytes were not 'RIFF' Gotta get riffier like the band Turnstile. They have cool riffs. Have you heard of them? \n");
        break;
    case 2:
        printf("heyy.... this isn't a wav file silly goose \n");
        break;
    case 3:
        printf("yo this format chunk isn't very 'fmt' enough. Try another file.. or dont. Your call \n");
        break;
    case 4:
        printf("this data header better be 'data' whether this data getter and setter is beta or better - Quote by M&M \n");
        break;
    case 5:
        printf("This value should be 1 and it's not. hEy sPeAkInG oF 1, diD yOu KnOw tAmE iMpAla iS jUsT onE gUy?????? \n");
        break;
    case 6:
        printf("There should be only 2 channels but you think you're better with more (or less) don't you. Try something with 2 channels like all the cool stereo kids \n");
        break;
    default:
        printf("        ...some other mysterious error has occured....               ....spooooky \n");
        break;
    }
}




// ITS HAVING ME CAST EVERYTHING AND SAYING POINTERS ARE NOT EQUAL TO POINTERS HELP







int main(int args, char** argv)
{

    /****************************************************
     * GET ALL OF THE THINGS
    ***************************************************/
    // get the command arguments are variables
    char *file_path_read = argv[1];
    char *file_path_write = argv[2];


    // load the wav file from the file input
    struct wav_file original_wav_file = load_file(file_path_read);

    // check if "original_wav_file is populated?"

    // extract header information and put into "original_wav_file.wav_header_pointer"
    int err = get_header(&original_wav_file);
    if(err != 0)
    {
        print_error_message(err);
        return err;
    }

    /****************************************************
     * SETTING UP FOR THE REVERSING
    ***************************************************/
    char* reversed = malloc(original_wav_file.file_size);
    // get bytes per sample from ((bits/sample)/8)
    //int step_size = (*original_wav_file.wav_header_pointer.bits_per_sample * 2) / 8;
    //int byte_rate = original_wav_file.wav_header_pointer.byte_rate;

    printf("%d\n",original_wav_file.file_size);
    short* g = (short*)&original_wav_file.original_data[34];
    short step_size = ((*g) * 2) / 8;
    //printf("%d\n",original_wav_file.wav_header_pointer.bits_per_sample);

    for(int i =0; i<44;i++){
        reversed[i] = original_wav_file.original_data[i];
    }

    //memcpy(reversed,&original_wav_file.original_data,44);

    /****************************************************
     * REVERSING THE WAV
    ***************************************************/
    // possibly wrong if the original_wav_file.file_size is not where we want it to be due to header?
    
    printf("Step size: %d\n\n", step_size);
    original_wav_file.file_size = original_wav_file.file_size;
    int i = original_wav_file.file_size - step_size;
    int j = 44;
    while(i > 44)
    {

        for(int h = 0; h<4; h++){
            reversed[j+h] = original_wav_file.data[i+h];
        }
        //memcpy(&reversed[j], &original_wav_file.data[i], step_size);
        printf("Copying %d to %d.\n", i, j);
        
        j = j + step_size;
        i = i - step_size;
    }

  /* int j = 44;
   //step_size = 2 * step_size;
    for(int i = (original_wav_file.file_size - step_size); i > 0; i -= step_size)
    {
        memcpy(&reversed[j], &original_wav_file.data[i], (size_t)step_size);
        j += step_size;
    }

*/
    // append header??
    int success = write_file(argv[2], reversed, original_wav_file.file_size);


    /****************************************************
     * CLEAN UP CLEAN UP EVERYBODY EVERYWHERE!
    ***************************************************/
    free(reversed);

    // file_lib_cleanup(); 
    // cleanup byte array made in read_file, which is then file_contents in "load_file(), and then broken into audio.wave_header_pointer and audio.data"

    return success;
}