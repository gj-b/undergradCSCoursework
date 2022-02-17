#include <stdio.h>
#include <stdlib.h>
#include "mastermind.h"

/******* TODO: PUT YOUR MASTERMIND CODE FROM HW1 HERE ******/
//Given a 4-digit number and a requested digit, the function returns the desired
//number. 
unsigned int extract_digit(unsigned int pattern, unsigned int digit)
{
    if(digit==0)
    {
        return pattern%10;
    }
    if(digit==1)
    {
        return (pattern%100)/10;
    }
    if(digit==2)
    {
        return (pattern%1000)/100;
    }
    if(digit==3)
    {
        return (pattern/1000);
    }
}


//Given a color, returns how many times that color appears in pattern. 
unsigned int num_of_color(unsigned int pattern, unsigned int color)
{
    int i, counter = 0;
    for(i=0;i<4;i++)
    {
    	if(color == extract_digit(pattern,i))
    		{
    			counter++;
    		}
    }
    return counter;
}

//Returns the number of exact matches occuring between the guess and the
//solution. 
unsigned int count_exact_matches(unsigned int guess, unsigned int solution)
{
    int i, counter = 0;
    for(i=0; i<4;i++)
    {
    	if(extract_digit(guess,i) == extract_digit(solution,i))
    	{
    		counter++;
    	}
    }
    return counter;
}

//Returns 1 if the given color is present in the solution. 
unsigned int color_present(unsigned int pattern, unsigned int color)
{
    int first, second, third, fourth;
    first = extract_digit(pattern,0);
    second = extract_digit(pattern,1);
    third = extract_digit(pattern,2);
    fourth = extract_digit(pattern,3);
    if(first == color || second == color || third == color || fourth == color)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//Given pattern and solution, returns how many times they have similar colors. 
unsigned int color_match_count(unsigned int pattern, unsigned int solution)
{
    int i, counter = 0;
    for(i=0; i<4; i++)
    {
    	counter += color_present(solution, extract_digit(pattern,i));
    }
    return counter;
}



//Given a guess and solution, returns the number of exact matches in 10th
//position and the number of additional color mathes in 0s position. 
unsigned int get_guess_feedback(unsigned int guess, unsigned int solution)
{
	

    if(guess>6666)
    {
    fprintf(stderr, "error: get_guess_feedback: your guess is too large. \n");
    return -1;
    }
    else if(guess<1111)
    {
    fprintf(stderr, "error: get_guess_feedback: your guess is too small. \n");
    return -1;
    }
    else if(solution>6666)
    {
    fprintf(stderr, "error: get_guess_feedback: "
    "your solution is too large. \n");
    return -1;
    }
    else if(solution<1111)
    {
    fprintf(stderr, "error: get_guess_feedback: your solution "
    "is too small. \n");
    return -1;
    }
    else if(extract_digit(guess,0)<1 || extract_digit(guess,1)<1
    || extract_digit(guess,2)<1 || extract_digit(guess,3)<1 
    || extract_digit(guess,0)>6 || extract_digit(guess,1)>6 
    || extract_digit(guess,2)>6 || extract_digit(guess,3)>6)
    {
    fprintf(stderr, "error: get_guess_feedback: for your guess, "
    "all colors must be in the 1 to  6 range.\n");
    return -1;
    }
    else if(extract_digit(solution,0)<1 || extract_digit(solution,1)<1
    || extract_digit(solution,2)<1 || extract_digit(solution,3)<1
    || extract_digit(solution,0)>6 || extract_digit(solution,1)>6 
    || extract_digit(solution,2)>6 || extract_digit(solution,3)>6)
    {
    fprintf(stderr, "error: get_guess_feedback: for your solution, "
    "all colors must be in the 1 to  6 range.\n");
    return -1;
    }

    else if(guess >= 1111 && guess <= 6666)
	{
		int exact_matches, color_matches, feedback;
    	exact_matches = count_exact_matches(guess,solution);
    	color_matches = color_match_count(guess,solution) - exact_matches;
    	feedback = exact_matches*10 + color_matches;
    	return feedback;
	}

    else
    {
    	fprintf(stderr, "Invalid input. Please input a number between 1111 and 6666.\n");
    	return -1;
    }
}

void print_mastermind_instructions()
{
	printf("Welcome to mastermind. I am thinking of a 4-number\n");
	printf("sequence. All four numbers are between 1 and 6.\n");
	printf("You have 12 guesses to guess it correctly.\n");
	printf("Each time you guess, I'll tell two things.\n");
	printf("1. How many numbers are correct and in the correct position.\n");
	printf("2. How many other numbers are correct but in the wrong position.\n");
	printf("Let's get started!!!\n");
}

/* get_new_code
 * Generates a 4-digit number, with each digit a number from 1 to 6, inclusive.
 * inputs:
 *   none
 * outputs:
 *   unsigned int - 4-digit number with each digit from 1 to 6
 */
unsigned int get_new_code()
{
	int i;
	int result = 0;
	for (i = 0; i < 4; i++)
	{
		result = result * 10;
		result = result + ((rand() % 6) + 1);
	}
	return result;
}

void play_mastermind()
{

	unsigned int guess_num = 0;
	unsigned int solution = 0;
	unsigned int guess = 0;
	unsigned int feedback = 0;

	print_mastermind_instructions();
	solution = get_new_code();
	printf("solution: %u\n",solution);

	// TODO: Limit number of guesses to 12 guesses
	do
	{	
		guess_num++;
		printf("Guess %d - ",guess_num);
		printf("Input your 4-digit guess: ");
		scanf("%u",&guess);

		feedback = get_guess_feedback(guess,solution);
			
		if(feedback == 40)
		{
			printf("Congratulations! Your guess of %u was correct!\n",
		guess);
			return;
		}

		else if(feedback != -1)
		{
			printf("Feedback: \n%u correct placement, correct number,\n",
		feedback / 10);
		printf("%u incorrect placement, correct number\n",
		feedback % 10);
		}

		else if(guess_num <= 12)
		{
			printf("Not quite - you still have %u guesses left!\n",
		12 - guess_num);
		}
	}
	while(guess_num < 12);
}

//IF GIVEN A BAD GUESS, PROVIDES ERRONOUS FEEDBACK.
