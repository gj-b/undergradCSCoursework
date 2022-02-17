#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw2.h"  // see how we're including the file again?
#include "mastermind.h" // another one!?! So that this code can be separate

//Test function for extract_digit.
unsigned int check_extract_digit(unsigned int pattern, unsigned int digit,
int expected_output)
{
    int output;
    output = extract_digit(pattern,digit);
    if(output == expected_output) 
    {
        printf("Test passed: Test extract_digit. Pattern : %d. Digit: %d."
            " Expected: %d. Output: %d.\n", pattern, digit,
            expected_output,output);
        return 1;
    }
    else
    {
        printf("Test failed: Test extract_digit. Expected: %d. vs." 
        " Output: %d.\n",expected_output,output);
        return 0;
    }
}

//Test function for num_of_color.
unsigned int check_num_of_color(unsigned int pattern, unsigned int color, 
unsigned int expected_output)
{
    int output;
    output = num_of_color(pattern,color);
    if(output == expected_output) 
    {
        printf("Test passed: Test num_of_color. Pattern : %d. Color: %d."
            " Expected number: %d. Output: %d.\n", pattern, color,
            expected_output,output);
        return 1;
    }
    else
    {
        printf("Test failed: Test num_of_color. Expected: %d. vs." 
        " Output: %d.\n",expected_output,output);
        return 0;
    }
}

//Test function for count_exact_matches.
unsigned int check_count_exact_matches(unsigned int guess, unsigned int solution, 
unsigned int expected_output)
{
    int output;
    output = count_exact_matches(guess,solution);
    if(output == expected_output) 
    {
        printf("Test passed: Test count_exact_matches. Solution: %d. Guess: %d."
            " Expected: %d. Output: %d.\n", solution, guess,
            expected_output,output);
        return 1;
    }
    else
    {
        printf("Test failed: Test count_exact_matches. Expected: %d. vs." 
        " Output: %d.\n",expected_output,output);
        return 0;
    }
}

//Test function for color_present.
unsigned int check_color_present(unsigned int pattern, unsigned int color, 
unsigned int expected_output)
{
    int output;
    output = color_present(pattern,color);
    if(output == expected_output) 
    {
        printf("Test passed: Test color_present. Pattern: %d. Color: %d."
            " Expected: %d. Output: %d.\n", pattern, color,
            expected_output,output);
        return 1;
    }
    else
    {
        printf("Test failed: Test color_present. Expected: %d. vs." 
        " Output: %d.\n",expected_output,output);
        return 0;
    }
}

//Test function for color_match_count.
unsigned int check_color_match_count(unsigned int pattern, unsigned int solution,
unsigned int expected_output)
{
    int output;
    output = color_match_count(pattern,solution);
    if(output == expected_output) 
    {
        printf("Test passed: Test color_match_count. Pattern: %d. Solution: %d."
            " Expected: %d. Output: %d.\n", pattern, solution,
            expected_output,output);
        return 1;
    }
    else
    {
        printf("Test failed: Test color_match_count. Expected: %d. vs." 
        " Output: %d.\n",expected_output,output);
        return 0;
    }
}

//Test function for get_guess_feedback.
unsigned int check_get_guess_feedback(unsigned int guess, unsigned int solution,
unsigned int expected_output)
{
    int output;
    output = get_guess_feedback(guess,solution);
    if(output == expected_output) 
    {
        printf("Test passed: Test get_guess_feedback. Pattern: %d. Solution: %d."
            " Expected: %d. Output: %d.\n", guess, solution,
            expected_output,output);
        return 1;
    }
    else
    {
        printf("Test failed: Test get_guess_feedback. Expected: %d. vs." 
        " Output: %d.\n",expected_output,output);
        return 0;
    }
}

void print_backwards_base_8_wrapper()
{
	unsigned int number;
        printf("What number would you like me to print? ");
        scanf("%u", &number);

        print_backwards_base_8(number);
}

//Test function for print_backwards_base_8.
void check_print_backwards_base_8(unsigned int num, unsigned int expected_output)
{

	printf("Print_backwards_base_8 test. Given number: %d. Expected Output: %d. Generated Output: ", num, expected_output);
	print_backwards_base_8(num);
	printf("\n");
}

unsigned int print_menu()
{
	unsigned int result;
	printf("\t0: Exit\n");
	printf("\t1: Mastermind\n");
	printf("\t2: 5 Questions\n");
	printf("\t3: Print Backwards in Base 8\n");
	printf("What would you like to play? ");
	scanf("%u", &result);

	return result;
}

int main()
{
	unsigned int total_tests = 0;
    unsigned int passed_tests = 0;

    int choice = 0;

    passed_tests = passed_tests + check_extract_digit(2497,0,7);
    total_tests++;
    passed_tests = passed_tests + check_extract_digit(2497,1,9);
    total_tests++;
    passed_tests = passed_tests + check_extract_digit(2497,2,4);
    total_tests++;
    passed_tests = passed_tests + check_extract_digit(2497,3,2);
    total_tests++;
    passed_tests = passed_tests + check_num_of_color(1234,1,1);
    total_tests++;
    passed_tests = passed_tests + check_num_of_color(4444,4,4);
    total_tests++;
    passed_tests = passed_tests + check_num_of_color(1111,2,0);
    total_tests++;
    passed_tests = passed_tests + check_count_exact_matches(1234,1234,4);
    total_tests++;
    passed_tests = passed_tests + check_count_exact_matches(1234,2341,0);
    total_tests++;
    passed_tests = passed_tests + check_count_exact_matches(1234,3256,1);
    total_tests++;
    passed_tests = passed_tests + check_color_present(1234,1,1);
    total_tests++;
    passed_tests = passed_tests + check_color_present(4353,1,0);
    total_tests++;
    passed_tests = passed_tests + check_color_match_count(1234, 1234, 4);
    total_tests++;
    passed_tests = passed_tests + check_color_match_count(1214,3421,4);
    total_tests++;
    passed_tests = passed_tests + check_color_match_count(5241,1214,3);
    total_tests++;
    passed_tests = passed_tests + check_get_guess_feedback(5241,1214,12);
    total_tests++;
    passed_tests = passed_tests + check_get_guess_feedback(1234,1234,40);
    total_tests++;
    passed_tests = passed_tests + check_get_guess_feedback(3131,1313,04);
    total_tests++;
    passed_tests = passed_tests + check_get_guess_feedback(93139,1313,-1);
    total_tests++;
    passed_tests = passed_tests + check_get_guess_feedback(3135,0,-1);
    total_tests++;
    passed_tests = passed_tests + check_get_guess_feedback(3139,1313,-1);
    total_tests++;
    printf("Passed %u out of %u tests.\n", passed_tests,total_tests);
    check_print_backwards_base_8(12,41);
    check_print_backwards_base_8(210,223);
    check_print_backwards_base_8(3600,207); //Really expect 0207.
    check_print_backwards_base_8(8,1);//Really expect 01.

    
    //Exercise 1 Tests.
    /*	Putting a non-integer breaks my code. But, doing that also breaks pre-given code
    	so I feel like that ok?

    	Solution 6251
    	Input 6251: "Congratulations, your guess of %s was correct!"
		Input 1234: 1 Correct placement, correct number. 1 correct number, incorrect placement. 
		Input 6241: 3 Correct placement, correct number. 0 correct number, incorrect placement. 
		Input 0: error, your guess is too small.
		Input 66666: error, your guess is too large.
		Input 1294: guess colors must be in 1-6 range. 
		Input "a": breaks code. Not sure how to fix this. Meaning, if one inputs anything that's not
		an integer, the code breaks. Hope we don't have to make tests against this. Don't feel like
		we learned how to. 
		
	//Exercise 2 Tests.
		Input 11111: Not quite sure, going to guess jellyfish.
		Input 00110: It is a pat of butter!
		Input 10110: It is an over!
		Input 100:  It is a pincushion!
		Input 1000: It is a squirrel!
		Input 10000: It is a see-saw!
		Input 1001: It is a jellyfish!
		Input 11001: It is a platypus!
		Input 11000: It is a camel!
		Input 1100: It is a pet gerbil!
		Input 0: It is a tetherball!
		Input 33333: Not quite sure, going to guess jellyfish.
		Again, if I input anything other than an integer the code breaks. Not too sure as to how 
		I should prevent this. 
    */

    do 
    {
	choice = print_menu();

	switch (choice) {
	   case (1): play_mastermind(); break;
	   case (2): play_5_questions(); break;
	   case (3): print_backwards_base_8_wrapper(); break;
	   case (0): break;
	   default: printf("Invalid choice. Try again.\n");
	}
	
    } while (choice != 0);
}
