#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw5.h"

/* Creates an empty string. Length 1 and null pointer : \0 */
safe_string* make_empty_string()
{
	safe_string *empty_str = malloc(sizeof(safe_string));
	empty_str->allocated_length = 1;
	empty_str->str = malloc(sizeof(char));
	empty_str->str[0] = '\0';
	return empty_str;
}

/*Takes the char * and converts it into a safe string. 
It needs to allocate new space for the string inside the safe string and initialize
 the string to match str.*/
safe_string* make_string(char *str)
{
	safe_string *safe_str = make_empty_string();
	safe_str->str = malloc(sizeof(char) * (strlen(str) + 1));
	safe_str->str = str;
	safe_str->allocated_length = strlen(str);
	return safe_str;
}

/* Copies a given string into its destination safely by re-allocating memory if needed.
*/
void safe_str_cpy(safe_string *dest, safe_string *src)
{
	if((dest->str != NULL) || (src->str != NULL)) 
	{
		if(dest->allocated_length > src->allocated_length)
		{
			strcpy(dest->str, src->str);
		}
		else
		{
			dest->str = malloc(sizeof(char) * ((src->allocated_length) + 1));
			strcpy(dest->str, src->str);
		}
		dest->allocated_length = src->allocated_length;
		return;
	}
	else
	{
		printf("Safe_str_cpy error: Given strings can't be NULL.\n");
	}
}

/* Adds a given with another safely by re-allocating memory if needed.
*/
void safe_str_cat(safe_string *dest, safe_string *src)
{
	char *str_1, *str_2;
	str_1 = dest->str;
	str_2 = src->str;

	if(dest->allocated_length > (dest->allocated_length + src->allocated_length))
	{
		strcat(str_1, str_2);
	}
	else
	{
		dest->str = malloc(sizeof(char) * (src->allocated_length + dest->allocated_length));
		strcat(str_1, str_2);
		dest->str = str_1;
		dest->allocated_length = dest->allocated_length + src->allocated_length;
	}
}

/* safe_strchr returns a pointer that points within the string that s holds - 
the first occurrence of the letter c within s's string. If c is not 
within s's string, it returns NULL. */
char *safe_strchr(safe_string *s, int c)
{
	for(int i = 0; i < s->allocated_length; i++)
	{
		if(s->str[i] == c)
		{
			return (s->str + i);
		}
	}
	return NULL;
}

//Helper function for strcmp. Given two characters, Says which one is bigger.
//-1: first is earlier. 0: identical 1: second is earlier.
int bigger_alphabetically(char c_1, char c_2)
{
	int cap_first, cap_second, value_first, value_second;
	if(c_1 > 90) //Checks to see if it's a lower case character.
	{
		//If it is lower case, gives the remainder. 'a' = 0 'b' = 1, ect.
		value_first = c_1 % 97; 
		cap_first = 0; //Cap_first is set to false b/c it's a lowercase char.
	}
	else
	{
		//If it is upper case, gives the remainder. 'A' = 0 'B'= 1, etc.
		value_first = c_1 % 65; 
		cap_first = 1; //Cap_first is set to true b/c it's upper case.
	}
	if(c_2 > 90)
	{
		//If it is lower case, gives the remainder. 'a' = 0 'b' = 1, ect.
		value_second = c_2 % 97; 
		cap_second = 0; //Cap_second is set to false b/c it's a lowercase char.
	}
	else
	{
		//If it is upper case, gives the remainder. 'A' = 0 'B'= 1, etc
		value_second = c_2 % 65; 
		cap_second = 1; //Cap_second is set to true b/c it's upper case.
	}

	//The return values follow given return rules for strcmp. 
	//So if c_1 is earlier alpha, return -1. If c_1 is later returns 1. 
	//If equal, returns 0.
	if(value_first<value_second) 
	{
		return -1; //Means that c_1 is earlier alphabetically.
	}
	else if(value_first>value_second)
	{
		return 1; //Means c_1 is later alphabetically. 
	}
	//If equal, now do tests for capital letters.
	else if(value_first == value_second) 
	{
		if(cap_first > cap_second) 
		{
			//Since they're equal but first was caps and second was not, 
			//first input comes before.
			return -1; 
		}
		else if(cap_first < cap_second)
		{
			//Since they're equal but first was not caps and second was, 
			//first input comes second.
			return 1; 
		}
		else
		{
			//The two character values are now proven equal and we can now return 
			//0 to show that. 
			return 0; 
		}
	}
}

/*safe_strcmp returns 0 if the strings within s1 and s2 are identical, -
1 if s1 is earlier alphabetically and 1 if s2 is later alphabetically. */
int safe_strcmp(safe_string *s1, safe_string *s2)
{
	int larger_len, result, i;
	if(s1->allocated_length > s2->allocated_length)
	{
		larger_len = s1->allocated_length;
	}
	else
	{
		larger_len = s2->allocated_length;
	}
	for(i = 0; i < larger_len; i++)
	{
		result = bigger_alphabetically(s1->str[i], s2->str[i]);
		if(result == -1)
			return -1;
		if(result == 1)
			return 1;
	}
	return 0;
}

