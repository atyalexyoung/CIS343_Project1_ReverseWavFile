#ifndef 	__H_LIB_FILE__
#define		__H_LIB_FILE__

/***
 * holds information about the header of the wav file
 * add information as needed
*/
struct wav_header
{
    
};


/***
 * holds information about the wav file
*/
struct wav_file
{
    struct wav_header* wav_header_pointer;
    int file_size;
    char* data;
};

/***
 * Gets the header information from the data
 * gets first 44 bytes of file, extracts data, creates header struct
*/
int get_header(char* data, char* wav_file);


/**
 * gets a file from disk into memory
 * calls read_file function from file library
 * takes retruned bytes and creates new wav_file
 * then set the header, data size, and pointer to data
*/
int load_file(char* data);


/***
 * gets the file from disc and loads into memory
 * takes wav_file and file path, prepares a byte array of the file
 * then calls write_file from file lib to write to disk
 * 
*/
int save_file(struct wav_file, char* file_path);










#endif
