#include <stdio.h>
#include <stdlib.h>
#include "hw2.h"

void play_5_qs_instructions()
{
	printf("Choose one of the following items to think about:\n");
	printf("duck-billed platypus, camel, pat of butter, squirrel, \n");
	printf("oven, pet gerbil, tetherball, jellyfish, pincushion, see-saw\n");

	printf("I will ask 5 questions and then guess which one you chose.\n");
	printf("Type 1 for yes and 0 for no for each question\n");
}

void play_5_questions()
{
	unsigned int response;
	unsigned int answer;

	play_5_qs_instructions();

	printf("Is it bigger than a breadbox? ");
	scanf("%u", &response);
	answer = response;
	printf("Is it alive? ");
	scanf("%u", &response);
	answer = answer*10 + response;
	printf("Is it found indoors? ");
	scanf("%u", &response);
	answer = answer*10 + response;
	printf("Is it found in the kitchen? ");
	scanf("%u", &response);
	answer = answer*10 + response;
	printf("Does it live in water? ");
	scanf("%u", &response);
	answer = answer*10 + response; 

	switch (answer)
	{
		case 110:
		printf("It is a pat of butter!\n");
		break;
		case 10110:
		printf("It is an oven!\n");
		break;
		case 100:
		printf("It is a pincushion!\n");
		break;
		case 1000:
		printf("It is a squirrel!\n");
		break;
		case 10000:
		printf("It is a see-saw!\n");
		break;
		case 1001:
		printf("It is a jellyfish!\n");
		break;
		case 11001:
		printf("It is a duck-billed platypus!\n");
		break;
		case 11000:
		printf("It is a camel!\n");
		break;
		case 1100:
		printf("It is a pet gerbil!\n");
		break;
		case 0:
		printf("It is a tetherball!\n");
		break;
		default:
			printf("Not quite sure, I'm going to guess jellyfish!\n");
	}
}

void print_backwards_base_8(unsigned int num)
{
	if((num / 8) == 0)
	{
		printf("%d \n",num);
	}
	else 
	{
		printf("%d",num % 8);
		print_backwards_base_8(num/8);
	}

}



