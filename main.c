#include <stdio.h>
#include "wav.h"





int main(int args, const char * argv[]){

 struct wav_file file = load_file("/Users/mitchellpeters/Documents/GitHub/CIS343_Project1_ReverseWavFile/Abdication.wav");

int err = get_header(file);


}