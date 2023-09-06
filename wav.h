#ifndef 	__H_LIB_FILE__
#define		__H_LIB_FILE__

/***
 * holds information about the header of the wav file
*/
struct wav_header
{

};


/***
 * holds information about the wav file
*/
struct wav_file
{
    struct wav_header* wave_header_pointer;
    int file_size;
    char* data;
};

/***
 * Gets the header information from the data
*/
int get_header(char* data, char* header_location);


/***
 * gets 
*/
int load_file(char* data);

int save_file(struct wav_file, char* file_path);










#endif
