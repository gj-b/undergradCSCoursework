#include <stdio.h>
#include <stdlib.h>
#include "warmup4.h"

/* count_vowels
 * search through str and count the number of vowels.
 * input: char *str - a string
 * output: int - the number of vowels in the string str
 *
 */
int count_vowels(char *str)
{
	int num = 0;
	int length = 0;
	for(int i =0; str[i] !='\0'; i++)
		{
			length = length + 1;
		}
	for(int f=0; f<length; f++)
	{
		if(str[f] == 'a' 
		|| str[f] == 'e'
		|| str[f] == 'i'
		|| str[f] == 'o'
		|| str[f] == 'u'
		|| str[f] == 'A'
		|| str[f] == 'E'
		|| str[f] == 'I'
		|| str[f] == 'O'
		|| str[f] == 'U'
		)
		{
			num = num + 1;
		}
	}
	return num;
}

/* make_lowercase
 * modify str such that all alphabetic characters are lower case
 * input: char *str - a string
 * output: no return value - str is out parameter
 */
void make_lowercase(char *str)
{
	int num = 0;
	int length = 0;
	for(int i =0; str[i] !='\0'; i++)
		{
			length = length + 1;
		}
	for(int f=0; f<length; f++)
	{
		if((str[f]>=65) && (str[f]<=90))
			{
				str[f] = str[f] + 32;
			}
	}
}

//Prints out the a given array of chars.
void print_string(char *str)
{
	for(int i=0; str[i] != '\0';i++)
	{
		printf("%c",str[i]);
	}
	printf("\n");
}

/* make_horizontal_stripes
 *   This produces an image stored in the red, green, and blue 2-d arrays.
 *   The image contains black and colored stripes. All stripes are 
 *   stripe_height. The stripe colors are indicated by stripe_color.
 *   The top stripe is colored. The image is heightxwidth.
 * inputs: 
 *   unsigned int red[ROWS][COLS],  - red component of resulting image pixels
 *   unsigned int green[ROWS][COLS], - green component of resulting image pixels
 *   unsigned int blue[ROWS][COLS],  - blue component of resulting image pixels
 *   unsigned int stripe_height,  - height of a single stripe
 *   unsigned int stripe_red,  - red component of stripe pixel
 *   unsigned int stripe_green,  - green component of stripe pixel
 *   unsigned int stripe_blue,  - blue component of stripe pixel
 *   unsigned int width,  - width of resulting image
 *   unsigned int height); - height of resulting image
 * 
 */
void make_horizontal_stripes( 
	unsigned int red[ROWS][COLS], 
	unsigned int green[ROWS][COLS], 
	unsigned int blue[ROWS][COLS], 
	unsigned int stripe_height, 
	unsigned int stripe_red, 
	unsigned int stripe_green, 
	unsigned int stripe_blue, 
	unsigned int width, 
	unsigned int height)
{
	if((width>COLS) || (height>ROWS))
	{
		fprintf(stderr, "%s\n", "Make_stripes: Not a valid width or height.");
	}
	else
	{
	int stripes;
	if(stripe_height != 0)
	{
		stripes = height / stripe_height;
	}
	else
	{
		stripes = 0;
	}
	for(int i=0; i<ROWS; i++)
			{
				for(int j=0; j<COLS; j++)
				{
					red[i][j] = 0;
					green[i][j] = 0;
					blue[i][j] = 0;
				}
			}
	for(int num_stripes = 0; num_stripes < stripes; num_stripes++)
	{
		if(num_stripes % 2 == 0)
			{
				for(int i= (num_stripes * stripe_height); 
					i<((num_stripes + 1) * stripe_height);
					 i++)
				{
					for(int j=0; j<COLS; j++)
					{
						red[i][j] = stripe_red;
						green[i][j] = stripe_green;
						blue[i][j] = stripe_blue;
					}
				}
			}
	}
	}
}

/* make_checker_board
 *   This produces an image stored in the red, green, and blue 2-d arrays.
 *   The image contains white and colored squares. All squares are 
 *   square_width x square_width. The square colors are indicated by 
 *   square_color. The image is heightxwidth. The top-left square is colored.
 * inputs: 
 *   unsigned int red[ROWS][COLS],  - red component of resulting image pixels
 *   unsigned int green[ROWS][COLS], - green component of resulting image pixels
 *   unsigned int blue[ROWS][COLS],  - blue component of resulting image pixels
 *   unsigned int square_height,  - height of a single square
 *   unsigned int square_red,  - red component of square pixel
 *   unsigned int square_green,  - green component of square pixel
 *   unsigned int square_blue,  - blue component of square pixel
 *   unsigned int width,  - width of resulting image
 *   unsigned int height); - height of resulting image
 * 
 */
void make_checker_board( 
        unsigned int red[ROWS][COLS],
        unsigned int green[ROWS][COLS],
        unsigned int blue[ROWS][COLS],
        unsigned int square_width,
        unsigned int square_red,
        unsigned int square_green,
        unsigned int square_blue,
        unsigned int width,
        unsigned int height)
{
	if((width>COLS) || (height>ROWS))
	{
		fprintf(stderr, "%s\n", 
			"Make_checker_board: Not a valid width or height.");
	}
	else
	{
	int squares; //Determines how many checkerts to have. 
	if(square_width != 0)
	{
		squares = height / square_width;
	}
	else
	{
		squares = 0;
	} 
	for(int i=0; i< width; i++) //Runs through and sets everything to white.
			{
				for(int j=0; j<width; j++)
				{
					red[i][j] = 255;
					green[i][j] = 255;
					blue[i][j] = 255;
				}
			}
	
	for(int row=0; row<squares; row++) //Runs through each checker.
	{
		for(int col=0; col<squares; col++)
		{
			if((row + col) % 2 == 0) 
			//If that checkers sum's remainder is equal to 0, paint it specified color. 
			 //equal to 0, paint it specified color. 
			{						
				for(int i=(col*square_width); i<((col + 1) * square_width); i++)
				{
					for(int j=(row*square_width); j<((row + 1) * square_width); j++)
					{
					red[i][j] = square_red;
					green[i][j] = square_green;
					blue[i][j] = square_blue;
					}
				}
			}
		}
		}
	}
}








