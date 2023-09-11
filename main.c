#include <stdio.h>
#include "wav.h"





int main(int args, const char * argv[]){
char* filepath = "/Users/mitchellpeters/Documents/GitHub/CIS343_Project1_ReverseWavFile/Abdication.wav";
 struct wav_file file = load_file(filepath);

int err = get_header(&file);


if(err != 0){
 printf("L");
}

char bytearray[file.file_size];

for(int i = file.file_size - 1; i >= 0; i -= 8){

}


}