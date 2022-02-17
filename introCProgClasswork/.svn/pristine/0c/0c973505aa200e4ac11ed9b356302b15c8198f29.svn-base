#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include "hw4_provided.h"
#include "warmup4.h"

//test function for count_vowels
int test_count_vowels(char *str, int expected_output)
{
	printf("Input: ");
	print_string(str);
	int num = count_vowels(str);
	if(expected_output == num)
	{
		printf("Test passed. Expected vowels: %d. Output: %d. \n",expected_output,num);
		return 1;
	}
	else
	{
		printf("Test failed. Expected vowels: %d. Output: %d. \n",expected_output,num);
		return 0;
	}
}

//test function for make_lowercase.
void test_make_lowercase(char *str)
{
	printf("Input: ");
	print_string(str);
	printf("Output: ");
	make_lowercase(str);
	print_string(str);
}

int main()
{
	// declare variables
	unsigned int r[ROWS][COLS];
        unsigned int g[ROWS][COLS];
        unsigned int b[ROWS][COLS];
        unsigned int width;
        unsigned int length;

    unsigned int total_tests = 0;
    unsigned int passed_tests = 0;

	char str1[] = {'H','o','w','d','y',' ','T','H','E','R','E','!','\0'};
	char str2[] = {'H','o','w','d','y',' ','T','H','E','R','E','!','Z','A','z','\0'};
	char str3[] = {'a','e','i','o','u','A','E','I','O','U','\0'};
	char str4[] = {'z','d','\0'};
	
	passed_tests += test_count_vowels(str1,3);
	total_tests++;
	passed_tests += test_count_vowels(str2,4);
	total_tests++;
	passed_tests += test_count_vowels(str3,10);
	total_tests++;
	passed_tests += test_count_vowels(str4,0);
	total_tests++;
	printf("Total tests: %d. Passed tests: %d.\n", total_tests,passed_tests);

	test_make_lowercase(str1);
	test_make_lowercase(str2);
	test_make_lowercase(str3);

	make_horizontal_stripes(r, g, b, 1, 30, 144, 255, ROWS, COLS);
	provided_print_image_to_html("my_horiz_stripes.html",r,g,b,ROWS, COLS);

	make_horizontal_stripes(r, g, b, 1, 30, 144, 255, 12, 12);
	provided_print_image_to_html("my_horiz_stripes_12.html",r,g,b,12, 12);

	make_horizontal_stripes(r, g, b, 1, 30, 144, 255, 52, 12);
	make_horizontal_stripes(r, g, b, 1, 30, 144, 255, 12, 52);

	make_horizontal_stripes(r, g, b, 0, 30, 144, 255, 12, 12);
	provided_print_image_to_html("my_horiz_stripes_black.html",r,g,b,12, 12);

	make_checker_board(r,g,b,4,30,144,255, 12, 12);
	provided_print_image_to_html("checkboard.html",r,g,b,12, 12);

	make_checker_board(r,g,b,4,30,144,255, 52, 12);
	make_checker_board(r,g,b,4,30,144,255, 12, 52);

	make_checker_board(r,g,b,1,30,144,255, 50, 50);
	provided_print_image_to_html("checkboard_2.html",r,g,b,12, 12);
}
