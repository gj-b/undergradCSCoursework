#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include "hw4.h"
#include "hw4_provided.h"


//Function I used to track the RGB values pre and post encoding.
void print_array_test(unsigned int arr[ROWS][COLS])
{
	for(int row=0; row<ROWS; row++)
	{
		for(int col=0; col<COLS; col++)
		{
			printf("%d ", arr[row][col]);
		}
	printf("\n");
	}
}

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
	unsigned int height, unsigned int width)
{
	for(int row=0; row<height; row++)
	{
		for(int col=0; col<width; col++)
		{
			res_r[row][col] = ref_r[row][col];
			res_b[row][col] = ref_b[row][col];
			res_g[row][col] = ref_g[row][col];

			if((hid_r[row][col] >= 128) && (ref_r[row][col] % 2 == 0))
			{
				res_r[row][col] += 1;
			}
			if((hid_g[row][col] >= 128) && (ref_g[row][col] % 2 == 0))
			{
				res_g[row][col] += 1;
			}
			if((hid_b[row][col] >= 128) && (ref_b[row][col] % 2 == 0))
			{
				res_b[row][col] += 1;
			}
			/*if(ref_r[row][col] % 2 ==0)
			{
				res_r[row][col] += 1;
			}
			if(ref_g[row][col] % 2 ==0)
			{
				res_g[row][col] += 1;
			}
			if(ref_b[row][col] % 2 ==0)
			{
				res_b[row][col] += 1;
			}
			*/
			if((hid_r[row][col] < 128) && (ref_r[row][col] % 2 == 1))
			{
				res_r[row][col] -= 1;
			}
			if((hid_g[row][col] < 128) && (ref_g[row][col] % 2 == 1))
			{
				res_g[row][col] -= 1;
			}
			if((hid_b[row][col] < 128) && (ref_b[row][col] % 2 == 1))
			{
				res_b[row][col] -= 1;
			}
			/*
			if(ref_r[row][col] % 2 ==1)
			{
				res_r[row][col] -= 1;
			}
			if(ref_g[row][col] % 2 ==1)
			{
				res_g[row][col] -= 1;
			}
			if(ref_b[row][col] % 2 ==1)
			{
				res_b[row][col] -= 1;
			}
			*/
		}
	}
}

//Extracts the encoded image by turning all even numbers into 0 RGB value and 
//all odd into 255 RGB value. 
void extract_image(
	unsigned int res_r[ROWS][COLS], 
	unsigned int res_g[ROWS][COLS], 
	unsigned int res_b[ROWS][COLS], 
	unsigned int hid_r[ROWS][COLS], 
	unsigned int hid_g[ROWS][COLS], 
	unsigned int hid_b[ROWS][COLS], 
	unsigned int height, unsigned int width)
{
	for(int row=0; row<height; row++)
	{
		for(int col=0; col<width; col++)
		{
			//for red.
			if(res_r[row][col] % 2 == 1)
			{
				hid_r[row][col] = 255;
			}
			else
			{
				hid_r[row][col] = 0;
			}
			//now for green.
			if(res_g[row][col] % 2 == 1)
			{
				hid_g[row][col] = 255;
			}
			else
			{
				hid_g[row][col] = 0;
			}
			//now for blue.
			if(res_b[row][col] % 2 == 1)
			{
				hid_b[row][col] = 255;
			}
			else
			{
				hid_b[row][col] = 0;
			}
		}
	}
}

//Function takes 3 pictures and does the work to encode it. 
//Ref_filename: Where you're hiding.
//Hid_filename: What you're hiding
//Enc_filename: Result
void encode(char *ref_filename, char *hid_filename, char *enc_filename)
{
	//declaring pointers
	unsigned int ref_width, ref_height, hid_width, hid_height, enc_width, enc_height;
	unsigned int red_ref[ROWS][COLS], green_ref[ROWS][COLS], blue_ref[ROWS][COLS];
	unsigned int red_hid[ROWS][COLS], green_hid[ROWS][COLS], blue_hid[ROWS][COLS];
	unsigned int red_enc[ROWS][COLS], green_enc[ROWS][COLS], blue_enc[ROWS][COLS];
	provided_read_png(ref_filename,red_ref,blue_ref,green_ref,&ref_width,&ref_height);
	provided_read_png(hid_filename,red_hid,green_hid,blue_hid,&hid_width,&hid_height);
	provided_read_png(enc_filename,red_enc,green_enc,blue_enc,&enc_width,&enc_height);
	hide_image(red_ref,green_ref,blue_ref,red_hid,green_hid,blue_hid,
		red_enc,green_enc,blue_enc,enc_width,enc_height);
	provided_write_png(enc_filename,red_enc,green_enc,blue_enc,enc_width,enc_height);
	//print_array_test(red_enc);
}

//Function that takes an encoded picture and decodes it. 
//Enc_filename: Encoded picture.
//Hid_filename: Result of the decoding. 
void decode(char *enc_filename, char *hid_filename)
{
	unsigned int hid_width, hid_height, enc_width, enc_height;
	unsigned int red_enc[ROWS][COLS], green_enc[ROWS][COLS], blue_enc[ROWS][COLS];
	unsigned int red_hid[ROWS][COLS], green_hid[ROWS][COLS], blue_hid[ROWS][COLS];
	provided_read_png(enc_filename,red_enc,green_enc,blue_enc,&enc_width,&enc_height);
	provided_read_png(hid_filename,red_hid,green_hid,blue_hid,&hid_width,&hid_height);
	extract_image(red_enc,green_enc,blue_enc,red_hid,green_hid,blue_hid,hid_width,hid_height);
	provided_write_png(hid_filename,red_hid,green_hid,blue_hid,hid_width,hid_height);
	//print_array_test(red_hid);
}

