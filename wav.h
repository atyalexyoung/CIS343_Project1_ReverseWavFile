#ifndef 	__H_LIB_FILE__
#define		__H_LIB_FILE__

/***
 * holds information about the header of the wav file
 * add information as needed
*/
struct wav_header
{
    char* riffy_boi; // MUST BE 'RIFF' 0-3
    int num_bytes; // number of bytes after subracting 8 4-7
    char* file_type; // MUST BE 'WAVE' 8-11
    char* format_chunk; // MUST BE 'fmt' 12-15
    int length_of_format_data; // 16-19
    short format_type; // 20-21
    short num_channels; // 22-23
    int sample_rate; // 24-27
    // 28-31 is (bits per sample * channels) / data_type_size
    // 32-33 (bits per sample * channels) / data_type_size
    char* bits_per_sample; // 34-35
    char* data_header; // MUST BE 'data' 36-39
    char* data_section_size; // 40-43
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
int get_header(struct wav_file);


/**
 * gets a file from disk into memory
 * calls read_file function from file library
 * takes retruned bytes and creates new wav_file
 * then set the header, data size, and pointer to data
*/
struct load_file(char* file_path);


/***
 * gets the file from disc and loads into memory
 * takes wav_file and file path, prepares a byte array of the file
 * then calls write_file from file lib to write to disk
 * 
*/
int save_file(struct wav_file, char* file_path);


#endif
