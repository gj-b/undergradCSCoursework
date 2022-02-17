#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <string.h>
#include "warmup5_provided.h"
#include "hw5.h"

//Helper function that displays the information of a safe-string.
void display_safe_string(safe_string *safe_str)
{
	printf("String Length: %d. String: ",safe_str->allocated_length);
	for(int i=0; i < 1 ;i++)
	{
		printf("%s",safe_str->str);
	}
	printf("\n");
}

int main( int argc, char *argv[] )
{
	//Test function for make_string.
	if(*argv[1] == '0')
	{
		display_safe_string(make_string(argv[2]));
	}
	if(*argv[1] == '1') //Can't quite figure out how to guard against null.
	{
		safe_string *test_1 = make_string(argv[2]);
		safe_string *test_2 = make_string(argv[3]);
		safe_str_cpy(test_1,test_2);
		display_safe_string(test_1);
		display_safe_string(test_2);
	}
	if(*argv[1] == '2')
	{
		printf("Given Strings: string1: %s. string2: %s.\n",argv[2],argv[3]);
		safe_string *test_1 = make_string(argv[2]);
		safe_string *test_2 = make_string(argv[3]);
		safe_str_cat(test_1,test_2);
		display_safe_string(test_1);
	}
	if(*argv[1] == '3')
	{
		int ascii_value = atoi(argv[3]);
		safe_string *test = make_string(argv[2]);
		printf("Given String: %s. Looking for char: %s\n",
		argv[2],argv[3]);
		char *from_char_on = safe_strchr(test,ascii_value);
		printf("If possible, string from that char on: %s.\n",from_char_on);
	}
	if(*argv[1] == '4')
	{
		safe_string *str_1 = make_string(argv[2]);
		safe_string *str_2 = make_string(argv[3]);
		int result = safe_strcmp(str_1,str_2);
		printf("Given Strings: string1: %s. string2: %s. \n",argv[2],argv[3]);
		printf("Result: %d\n",result);
		if(result == -1)
		{
			printf("Meaning, first string is earlier alphabetically.\n");
		}
		else if(result == 0)
		{
			printf("Meaning, strings are identical.\n");
		}
		else if(result == 1)
		{
			printf("Meaning, second string is earlier alphabetically.\n");
		}

	else
	{
		printf("Please input a value to test.\n");
	}
	return 0;
	}
}