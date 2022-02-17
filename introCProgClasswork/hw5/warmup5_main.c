#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <string.h>
#include "warmup5_provided.h"
#include "warmup5.h"

//Test function for string_concat
void test_string_concat(char *str1, char *str2)
{
	printf("String1: %s.\nString2: %s.\n",str1,str2);
	char *safe_str = safe_str_concat(str1,str2);
	printf("Strings Together: %s\n",safe_str);
}

//Prints out the informtion of an int_vector struct.
void print_int_vector_info(int_vector *vector)
{
	printf("Size: %d. Array: ",vector->allocated_size);
	for(int i = 0; i<vector->allocated_size; i++)
	{
		printf("%d",vector->array[i]);
	}
	printf("\n");
}

//Test function for write_value.
void test_write_value(int_vector *vector, unsigned int index, int value)
{
	print_int_vector_info(vector);
	write_value(vector,index,value);
	print_int_vector_info(vector);
}

//Test function for read value.
void test_read_value(int_vector *vector, unsigned int index)
{
	printf("Given Index: %d. Value stored there, if possible: %d.\n", index, 
		read_value(vector,index));
}

int main( int argc, char *argv[] )
{
	
	if(*argv[1] == '0')
	{
		printf("Testing program: string_concat.\n");
		char *str1 = argv[2];
		char *str2 = argv[3];
		test_string_concat(str1,str2);
	}
	if(*argv[1] == '1')
	{
		printf("hi\n");
		//Perform all my testing with a singular int_vector
		int_vector* test = make_init_array();
		print_int_vector_info(test);
		write_value(test,4,1);
		print_int_vector_info(test);
		write_value(test,17,2);
		print_int_vector_info(test);
		write_value(test,50,1);
		print_int_vector_info(test);
		write_value(test,204,3);
		print_int_vector_info(test);
	}
	if(*argv[1] == '2')
	{
		int_vector* test = make_init_array();
		write_value(test,4,1);
		print_int_vector_info(test);
		test_read_value(test,4);
		test_read_value(test,6);
		test_read_value(test,0);
	}
	if(*argv[1] == '3')
	{
		pixel test_colors;
		test_colors.red = (int)argv[2];
		test_colors.green = (int)argv[3];
		test_colors.blue = (int)argv[4];
		provided_write_png_struct("test_image.png",
			make_and_init_image(50,50,test_colors),50,50);
	}
	
	return 0;
}
