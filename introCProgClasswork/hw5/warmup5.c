#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "warmup5.h"

/*A function that, instead of copying str2 to the end of str1, allocates a brand 
new string that will hold both str1 and str2. Then it copies both strings over, 
str1 at the front and str2 at the back. It returns a pointer to that new string.*/
char *safe_str_concat(char *str1, char *str2)
{
	//Tests for NULL error as that causes seg fault.
	if((str1 != NULL) || (str2 != NULL)) 
	{
		char *safe_str = malloc((sizeof(char))*(strlen(str1) + strlen(str2) + 1));
		strcpy(safe_str, str1);
		strcat(safe_str, str2);
		return safe_str;
	}
	else
	{
		printf("Safe_str_concat error: Functions can't be NULL.\n");
	}
}

/*Allocates the int_vector and initializes the values for an array with 0 items*/
int_vector *make_init_array()
{
	int_vector *created_vector = malloc(sizeof(int_vector));
	created_vector->allocated_size = 0;
	created_vector->array = malloc(sizeof(int) * 0);
	return created_vector;
}

/*Depending on index given, does different things to size.
If within, just adds that index's value. 
If out but <16, bumps memory storage to 16 and stores value.
If out and less than double in size, doubles size and stores value. 
If out and more than double in mem. size, goes to new needed size +1.*/
void write_value(int_vector *vector, unsigned int index, int value)
{
	if(index < vector->allocated_size) //Index is within mem. Assigns value.
	{
		vector->array[index] = value;
		return;
	}

	int size = vector->allocated_size; //causes less writing and is more efficient.
	int_vector *temp = malloc(sizeof(int_vector)); //The temp array.
	
	//Beginning of size checks, self-explanatory.
	if(index > size)
	{
		if ((size < 8) && (index < 16))
		{
			temp->array = malloc(sizeof(int)*16);
			temp->allocated_size = 16;
		}
		else if (index < (2*size))
		{
			temp->array = malloc(sizeof(int)*(index*2));
			temp->allocated_size = index*2;
		}
		else
		{
			temp->array = malloc(sizeof(int) * (index + 1));
			temp->allocated_size = index + 1;
		}
	}
	
	//Copies over all elements into the temp array and assigns the asked value.
	for(int i=0; i<size;i++)
	{
		temp->array[i] = vector->array[i];
	}
	temp->array[index] = value;
	//Frees given vector before re-giving it new values.
	free(vector);
	vector = malloc(sizeof(temp));
	vector->allocated_size = temp->allocated_size;
	vector->array = temp->array;
	free(temp); //Don't think this is needed but better to just free it. 
}

/*If the programmer reads an element of the array beyond the length, return 0
else return requested value. */
int read_value(int_vector *vector, unsigned int index)
{
	if(index > (vector->allocated_size - 1))
	{
		return 0;
	}
	return vector->array[index];
}

/*Assigns every element in a double pointer to the given colors. */
pixel** make_and_init_image(int height, int width, pixel color)
{
	pixel **rows = malloc(sizeof(pixel*) * height);
	unsigned int red_val = color.red;
	unsigned int green_val = color.green;
	unsigned int blue_val = color.blue;
	for(int i = 0; i<height; i++)
	{
		rows[i] = (pixel*) malloc(sizeof(pixel*) * width);
		for(int j=0; j<width; j++)
		{
			rows[i][j].red = red_val;
			rows[i][j].green = green_val;
			rows[i][j].blue = blue_val;
		}
	}
	return rows;
}

