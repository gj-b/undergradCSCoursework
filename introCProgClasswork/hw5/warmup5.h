#include "warmup5_provided.h"

#ifndef WARMUP5_H
#define WARMUP5_H

/*A function that, instead of copying str2 to the end of str1, allocates a brand 
new string that will hold both str1 and str2. Then it copies both strings over, 
str1 at the front and str2 at the back. It returns a pointer to that new string.*/
char *safe_str_concat(char *str1, char *str2);

typedef struct {
	unsigned int allocated_size;
	int *array;
} int_vector;

/*Allocates the int_vector and initializes the values for an array with 0 items*/
int_vector* make_init_array();

/*Depending on index given, does different things to size.
If within, just adds that index's value. 
If out but <16, bumps memory storage to 16 and stores value.
If out and less than double in size, doubles size and stores value. 
If out and more than double in mem. size, goes to new needed size +1.*/
void write_value(int_vector *vector, unsigned int index, int value);

/*If the programmer reads an element of the array beyond the length, return 0
else return requested value. */
int read_value(int_vector *vector, unsigned int index);

/*Assigns every element in a double pointer to the given colors. */
pixel** make_and_init_image(int height, int width, pixel color);





































#endif