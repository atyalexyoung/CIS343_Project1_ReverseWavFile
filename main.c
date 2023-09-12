#include <stdio.h>
#include <stdlib.h>
#include "wav.h"
#include "file_lib.h"


int print_error_message(int error)
{
    switch (error)
    {
    case 1:
        printf("The first 4 bytes were not 'RIFF' Gotta get riffier like the band Turnstile. They have cool riffs. Have you heard of them?");
        break;
    case 2:
        printf("heyy.... this isn't a wav file silly goose");
        break;
    case 3:
        printf("yo this format chunk isn't very 'fmt' enough. Try another file.. or dont. Your call");
        break;
    case 4:
        printf("this data header better be 'data' whether this data getter and setter is beta or better - Quote by M&M");
        break;
    case 5:
        printf("This value should be 1 and it's not. hEy sPeAkInG oF 1, diD yOu KnOw tAmE iMpAla iS jUsT onE gUy??????");
        break;
    case 6:
        printf("There should be only 2 channels but you think you're better with more (or less) don't you. Try something with 2 channels like all the cool stereo kids");
        break;
    case 7:
        printf("This one should be (n - 8) where n = the number of bytes of the file. Because why wouldn't it be. But it's not in your case so idk try something else.");
        break;
    default:
        printf("        ...some other mysterious error has occured....               ....spooooky");
        break;
    }
}


int main(int args, const char * argv[])
{

    // get general file path and load the wav file into the struct
    char* filepath = "/Abdication.wav";
    struct wav_file original_wav_file = load_file(filepath);

    // extract header information
    int err = get_header(&original_wav_file);


    if(err != 0)
    {
        print_error_message(err);
        return err;
    }

    // bits per sample -> bytes

    char reversed_wav_file[original_wav_file.file_size];
    int byte_rate = original_wav_file.wav_header_pointer->byte_rate;

    int j = 0;
    for(int i = (original_wav_file.file_size - 1); i >= 0; i -= byte_rate)
    {
        // make a little byte arrays instead of just using one address???
        reversed_wav_file[j] = original_wav_file.data[i];
        j+=byte_rate;
    }

}