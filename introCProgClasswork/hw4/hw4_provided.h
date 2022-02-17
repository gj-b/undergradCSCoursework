#ifndef HW4_PROVIDED_H
#define HW4_PROVIDED_H

#define ROWS 50
#define COLS 50

#define QUALITY 100

void read_png_file(char* file_name);

void write_png_file(char* file_name);

void buffer_to_arrays(unsigned int red[ROWS][COLS], 
    unsigned int green[ROWS][COLS], 
    unsigned int blue[ROWS][COLS]);

void arrays_to_buffer(unsigned int red[ROWS][COLS], 
    unsigned int green[ROWS][COLS], 
    unsigned int blue[ROWS][COLS]);

void free_buffer(void);

int provided_read_png(char *filename, 
    unsigned int red[ROWS][COLS], 
    unsigned int green[ROWS][COLS], 
    unsigned int blue[ROWS][COLS], 
    unsigned int *image_width, 
    unsigned int *image_length);

int provided_write_png(char *filename, 
    unsigned int red[ROWS][COLS], 
    unsigned int green[ROWS][COLS], 
    unsigned int blue[ROWS][COLS], 
    unsigned int image_width, 
    unsigned int image_length);

void abort_(const char * s, ...);

int provided_print_image_to_html(char *filename, unsigned int red[ROWS][COLS],
    unsigned int green[ROWS][COLS],
    unsigned int blue[ROWS][COLS],
    unsigned int image_width,
    unsigned int image_height);

#endif /* HW4_PROVIDED_H */
