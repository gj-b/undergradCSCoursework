#ifndef HW4_H 
#define HW4_H 

#define ROWS 50
#define COLS 50

//Function I used to track the RGB values pre and post encoding.
void print_array_test(unsigned int arr[ROWS][COLS]);

//Encodes the hid_image inside the ref_image using even and odd encryption. 
void hide_image(
	unsigned int ref_r[ROWS][COLS], 
	unsigned int ref_g[ROWS][COLS], 
	unsigned int ref_b[ROWS][COLS], 
	unsigned int hid_r[ROWS][COLS], 
	unsigned int hid_g[ROWS][COLS], 
	unsigned int hid_b[ROWS][COLS], 
	unsigned int res_r[ROWS][COLS], 
	unsigned int res_g[ROWS][COLS], 
	unsigned int res_b[ROWS][COLS], 
	unsigned int height, unsigned int width);

//Extracts the encoded image by turning all even numbers into 0 RGB value and 
//all odd into 255 RGB value. 
void extract_image(
	unsigned int res_r[ROWS][COLS], 
	unsigned int res_g[ROWS][COLS], 
	unsigned int res_b[ROWS][COLS], 
	unsigned int hid_r[ROWS][COLS], 
	unsigned int hid_g[ROWS][COLS], 
	unsigned int hid_b[ROWS][COLS], 
	unsigned int height, unsigned int width);

//Function takes 3 pictures and does the work to encode it. 
//Ref_filename: Where you're hiding.
//Hid_filename: What you're hiding
//Enc_filename: Result
void encode(char *ref_filename, char *hid_filename, char *enc_filename);

//Function that takes an encoded picture and decodes it. 
//Enc_filename: Encoded picture.
//Hid_filename: Result of the decoding. 
void decode(char *enc_filename, char *hid_filename);

































#endif